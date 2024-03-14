module ysyx_23060180_cpu_core(
    input clk,
    input rstn_in,
    output mem_rd,
    output [31:0] mem_raddr,
    input [31:0] mem_rdata
);

import "DPI-C" function void ebreak();

// sys states
parameter IDLE = 0;
parameter FETCH = 1;
parameter DECODE = 2;
parameter EXECUTE = 3;
parameter MEMORY = 4;
parameter STATE_BITS = 3;
reg [STATE_BITS-1:0] state;

// registers
reg [31:0] R [0:31];

always @(posedge clk or negedge rstn_in) begin
    if (!rstn_in) begin
        for (int i = 0; i < 32; i = i + 1) begin
            R[i] <= 32'h0;
        end
    end
    else begin
        R[0] <= 32'h0;
        case (state)
            EXECUTE: begin
                if (alu_result_valid && (alu_result_rd != 0)) begin
                    R[alu_result_rd] <= alu_result;
                end
            end
        endcase
    end
end

// aysnc reset, synchronous load
reg rstn_d1;
reg rstn_d2;
wire rstn;
always @(posedge clk or negedge rstn_in) begin
    if (!rstn_in) begin
        rstn_d1 <= 1'b0;
        rstn_d2 <= 1'b0;
    end
    else begin
        rstn_d1 <= 1'b1;
        rstn_d2 <= rstn_d1;
    end
end
assign rstn = rstn_d2;

// pc
reg [31:0] pc;
reg [31:0] pc_next;
always @(posedge clk or negedge rstn) begin
    if (!rstn) begin
        pc <= 32'h80000000;
    end
    else begin
        pc <= pc_next;
    end
end

// fetch stage
reg [31:0] instr;
reg mem_rd_d1;
reg mem_rd_d2;
wire mem_rdata_valid;
wire instr_valid;

assign mem_rd = (state == IDLE);
assign mem_raddr = pc;

always @(posedge clk) begin
    mem_rd_d1 <= mem_rd;
    mem_rd_d2 <= mem_rd_d1;
end
assign mem_rdata_valid = mem_rd;
assign instr_valid = mem_rd_d1;

always @(posedge clk or negedge rstn) begin
    if (!rstn) begin
        instr <= 32'h0;
    end
    else if (mem_rdata_valid) begin
        instr <= mem_rdata;
    end
end

// decode stage
wire [6:0] opcode;
wire [4:0] rs1;
wire [4:0] rs2;
wire [4:0] rd;
wire [2:0] func3;
wire [11:0] func12;
wire [31:0] imm;
wire [31:0] immu;
reg alu_valid;
reg e_valid;
reg [31:0] oprand1;
reg [31:0] oprand2;
reg [4:0] oprand_rd;

assign opcode = instr[6:0];
assign rs1 = instr[19:15];
assign rs2 = instr[24:20];
assign rd = instr[11:7];
assign func3 = instr[14:12];
assign func12 = instr[31:20];
assign imm = {20'b0, instr[31:20]};
assign immu = {instr[31:12], 12'b0};

always @(posedge clk or negedge rstn) begin
    if (!rstn) begin
        oprand_rd <= 5'b0;
    end
    else if (instr_valid) begin
        oprand_rd <= rd;
    end
end

always @(posedge clk or negedge rstn) begin
    if (!rstn) begin
        oprand1 <= 32'h0;
        oprand2 <= 32'h0;
        alu_valid <= 1'b0;
        e_valid <= 1'b0;
    end
    else if (instr_valid) begin
        alu_valid <= 1'b0;
        e_valid <= 1'b0;
        oprand1 <= R[rs1];
        case (opcode)
            7'b0010111: begin   // auipc
                oprand1 <= 0;
                oprand2 <= immu;
                alu_valid <= 1'b1;
            end
            7'b0010011: begin
                oprand2 <= imm;
                alu_valid <= 1'b1;
            end
            7'b1110011: begin
                if (func3 == 3'b000) begin
                    oprand2 <= imm;
                    e_valid <= 1'b1;
                end
            end
            default: begin
                alu_valid <= 1'b0;
                e_valid <= 1'b0;
            end
        endcase
    end
    else begin
        alu_valid <= 1'b0;
        e_valid <= 1'b0;
    end
end

// execute stage
reg [31:0] alu_result;
reg alu_result_valid;
reg [4:0] alu_result_rd;

always @(posedge clk or negedge rstn) begin
    if (!rstn) begin
        alu_result_valid <= 1'b0;
        alu_result <= 32'h0;
        alu_result_rd <= 5'b0;
    end
    else if (alu_valid) begin
        alu_result_valid <= 1'b1;
        alu_result <= oprand1 + oprand2;
        alu_result_rd <= oprand_rd;
    end
    else begin
        alu_result_valid <= 1'b0;
    end
end

always @(posedge clk or negedge rstn) begin
    if (rstn && e_valid && func12 == 12'h001) begin
        ebreak();
    end
end

// pc control
always @* begin
    pc_next = pc;
    case (state)
        EXECUTE: begin
            if (alu_result_valid) begin
                pc_next = pc + 4;
            end
        end
    endcase
end

// memory stage

// state machine
always @(posedge clk or negedge rstn) begin
    if (!rstn) begin
        state <= IDLE;
    end
    else begin
        case (state)
            IDLE: begin
                state <= FETCH;
            end
            FETCH: begin
                if (instr_valid) begin
                    state <= DECODE;
                end
            end
            DECODE: begin
                if (alu_valid || e_valid) begin
                    state <= EXECUTE;
                end
            end
            EXECUTE: begin
                if (alu_result_valid) begin
                    state <= IDLE;
                end
            end
        endcase
    end
end

endmodule
