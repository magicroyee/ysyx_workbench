module ysyx_23060180_cpu_core(
    input clk,
    input rstn_in,
    output mem_rd,
    output mem_wr,
    output reg [31:0] mem_raddr,
    input [31:0] mem_rdata,
    output reg [31:0] mem_wdata,
    output reg [3:0] mem_wbit_en
);

reg s_valid;
reg l_valid;
reg l_loading;
wire execute_finish;

wire [6:0] opcode;
wire [4:0] rs1;
wire [4:0] rs2;
wire [4:0] rd;
wire [2:0] func3;
wire [11:0] func12;
wire [31:0] imm;
wire [31:0] immu;
wire [31:0] imms;
wire [31:0] immj;
wire [31:0] immb;
reg alu_valid;
reg e_valid; // ebreak
reg jump_valid;
reg store_valid;
reg load_valid;
reg [31:0] oprand1;
reg [31:0] oprand2;
reg [4:0] oprand_rd;

import "DPI-C" context function void ebreak(); 
import "DPI-C" context function void jump_en(input int addr, input int pc, input int rd, input int rs1); 
export "DPI-C" task reg_value; 

task reg_value;
    input [4:0] reg_num;
    output [31:0] value;
    value = R[reg_num];
endtask

// sys states
parameter IDLE = 0;
parameter FETCH = 1;
parameter DECODE = 2;
parameter EXECUTE = 3;
parameter MEMORY = 4;
parameter WRITEBACK = 5;
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
                if (execute_finish && (alu_result_rd != 0)) begin
                    if (jump_valid_d1) begin
                        R[alu_result_rd] <= pc + 4;
                    end
                    else if (l_loading) begin
                        case(func3)
                        3'b000: begin // lb
                            R[alu_result_rd] <= {{24{mem_rdata[7]}}, mem_rdata[7:0]};
                        end
                        3'b001: begin // lh
                            R[alu_result_rd] <= {{16{mem_rdata[15]}}, mem_rdata[15:0]};
                        end
                        3'b010: begin // lw
                            R[alu_result_rd] <= mem_rdata;
                        end
                        3'b100: begin // lbu
                            R[alu_result_rd] <= {24'b0, mem_rdata[7:0]};
                        end
                        3'b101: begin // lhu
                            R[alu_result_rd] <= {16'b0, mem_rdata[15:0]};
                        end
                        default: begin
                            R[alu_result_rd] <= mem_rdata;
                        end
                        endcase
                    end
                    else begin
                        R[alu_result_rd] <= alu_result;
                    end
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

assign mem_rd = (state == IDLE) || (state == WRITEBACK) || l_valid;
always @(*) begin
    if (s_valid || l_valid) begin
        mem_raddr = alu_result;
    end
    else begin
        mem_raddr = pc;
    end
end
assign mem_wr = s_valid;
always @(*) begin
    if (s_valid) begin
        mem_wdata = R[rs2];
        case (func3)
            3'b000: mem_wbit_en = 4'd1;
            3'b001: mem_wbit_en = 4'd2;
            3'b010: mem_wbit_en = 4'd4;
            default: mem_wbit_en = 4'd0;
        endcase
    end
    else begin
        mem_wdata = 32'h0;
        mem_wbit_en = 4'd0;
    end
end

always @(posedge clk) begin
    mem_rd_d1 <= mem_rd;
    mem_rd_d2 <= mem_rd_d1;
end
assign mem_rdata_valid = mem_rd_d1;
assign instr_valid = mem_rd_d2;

always @(posedge clk or negedge rstn) begin
    if (!rstn) begin
        instr <= 32'h0;
    end
    else if (mem_rdata_valid) begin
        instr <= mem_rdata;
    end
end

// decode stage

assign opcode = instr[6:0];
assign rs1 = instr[19:15];
assign rs2 = instr[24:20];
assign rd = instr[11:7];
assign func3 = instr[14:12];
assign func12 = instr[31:20];
assign imm = {{20{instr[31]}}, instr[31:20]};
assign immu = {instr[31:12], 12'b0};
assign imms = {{20{instr[31]}}, instr[31:25], instr[11:7]};
assign immj = {{11{instr[31]}}, instr[31], instr[19:12], instr[20], instr[30:21], 1'b0};
assign immb = {{12{instr[31]}}, instr[31], instr[7], instr[30:25], instr[11:8], 1'b0};

reg b_cmp;
always @* begin
    case({R[rs1][31], R[rs2][31]})
    2'b00: b_cmp = R[rs1] < R[rs2];
    2'b01: b_cmp = 1'b0;
    2'b10: b_cmp = 1'b1;
    2'b11: b_cmp = R[rs1] < R[rs2];
    endcase
end

always @(posedge clk or negedge rstn) begin
    if (!rstn) begin
        oprand1 <= 32'h0;
        oprand2 <= 32'h0;
        alu_valid <= 1'b0;
        e_valid <= 1'b0;
        jump_valid <= 1'b0;
        store_valid <= 1'b0;
        load_valid <= 1'b0;
        oprand_rd <= 5'b0;
    end
    else if (instr_valid) begin
        oprand1 <= R[rs1];
        oprand2 <= 32'h0;
        alu_valid <= 1'b0;
        jump_valid <= 1'b0;
        oprand_rd <= rd;
        store_valid <= 1'b0;
        load_valid <= 1'b0;
        case (opcode)
            7'b0110111: begin   // lui
                oprand1 <= 32'd0;
                oprand2 <= immu;
                alu_valid <= 1'b1;
            end
            7'b0010111: begin   // auipc
                oprand1 <= pc;
                oprand2 <= immu;
                alu_valid <= 1'b1;
            end
            7'b1101111: begin   // jal
                oprand1 <= pc;
                oprand2 <= immj;
                alu_valid <= 1'b1;
                jump_valid <= 1'b1;
            end
            7'b1100111: begin   // jalr
                oprand2 <= imm;
                alu_valid <= 1'b1;
                jump_valid <= 1'b1;
            end
            7'b1100011: begin   // beq, bne, blt, bge, bltu, bgeu
                oprand1 <= pc;
                oprand2 <= immb;
                oprand_rd <= 5'b0;
                case(func3)
                3'b000: begin // beq
                    alu_valid <= R[rs1] == R[rs2];
                    jump_valid <= R[rs1] == R[rs2];
                end
                3'b001: begin // bne
                    alu_valid <= R[rs1] != R[rs2];
                    jump_valid <= R[rs1] != R[rs2];
                end
                3'b100: begin // blt
                    alu_valid <= b_cmp;
                    jump_valid <= b_cmp;
                end
                3'b101: begin // bge
                    alu_valid <= !b_cmp;
                    jump_valid <= !b_cmp;
                end
                3'b110: begin // bltu
                    alu_valid <= R[rs1] < R[rs2];
                    jump_valid <= R[rs1] < R[rs2];
                end
                3'b111: begin // bgeu
                    alu_valid <= R[rs1] >= R[rs2];
                    jump_valid <= R[rs1] >= R[rs2];
                end
                default: begin
                    alu_valid <= 1'b0;
                    jump_valid <= 1'b0;
                end
                endcase
            end
            7'b0100011: begin   // sw, sh, sb
                oprand2 <= imms;
                alu_valid <= 1'b1;
                oprand_rd <= 5'b0;
                store_valid <= 1'b1;
            end
            7'b0000011: begin   // lb, lh, lw, lbu, lhu
                oprand2 <= imm;
                alu_valid <= 1'b1;
                oprand_rd <= rd;
                load_valid <= 1'b1;
            end
            7'b0010011: begin   // addi, slti, sltiu, xori, ori, andi
                oprand2 <= imm;
                alu_valid <= 1'b1;
            end
            7'b1110011: begin   // ebreak
                if (func3 == 3'b000) begin
                    oprand2 <= imm;
                    e_valid <= 1'b1;
                end
            end
            default: begin
                alu_valid <= 1'b0;
            end
        endcase
    end
    else begin
        alu_valid <= 1'b0;
        jump_valid <= 1'b0;
        store_valid <= 1'b0;
        load_valid <= 1'b0;
    end
end

// execute stage
reg [31:0] alu_result;
reg alu_result_valid;
reg [4:0] alu_result_rd;
reg jump_valid_d1;
// wire [31:0] oprand2_com
// wire [32:0] op1_sub_op2;
// assign oprand2_com = ~oprand2_com + 1'b1;
// assign op1_sub_op2 = oprand1 + oprand2_com;

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
        if (opcode == 7'b0010011 || opcode == 7'b0110011) begin
            case(func3)
            3'b000: begin // addi
                alu_result <= oprand1 + oprand2;
            end
            3'b010: begin // slti
                case({oprand1[31], oprand2[31]})
                2'b00: alu_result <= oprand1 < oprand2;
                2'b01: alu_result <= 1'b0;
                2'b10: alu_result <= 1'b1;
                2'b11: alu_result <= oprand1 < oprand2;
                endcase
            end
            3'b011: begin // sltiu
                alu_result <= oprand1 < oprand2;
            end
            3'b100: begin // xori
                alu_result <= oprand1 ^ oprand2;
            end
            3'b110: begin // ori
                alu_result <= oprand1 | oprand2;
            end
            3'b111: begin // andi
                alu_result <= oprand1 & oprand2;
            end
            3'b001: begin // slli
                alu_result <= oprand1 << oprand2[4:0];
            end
            3'b101: begin // srli, srai
                case(func12[11])
                1'b0: alu_result <= oprand1 >> oprand2[4:0];
                1'b1: alu_result <= oprand1 >>> oprand2[4:0];
                endcase
            end
            endcase
        end
        else if (opcode == 7'b1100111) begin
            alu_result <= oprand1 + oprand2;
        end
    end
    else begin
        alu_result_valid <= 1'b0;
    end
end

always @(posedge clk or negedge rstn) begin
    if (!rstn) begin
        l_valid <= 1'b0;
        s_valid <= 1'b0;
    end
    else begin
        l_valid <= load_valid;
        s_valid <= store_valid;
    end
end

always @(posedge clk or negedge rstn) begin
    if (!rstn) begin
        l_loading <= 1'b0;
    end
    else if (load_valid) begin
        l_loading <= 1'b1;
    end
    else if (mem_rdata_valid) begin
        l_loading <= 1'b0;
    end
end

assign execute_finish = (~l_loading && (alu_result_valid || e_valid)) || (l_loading && mem_rdata_valid);

always @(posedge clk or negedge rstn) begin
    if (rstn && (state==WRITEBACK) && e_valid && func12 == 12'h001) begin
        ebreak();
    end
end

always @(posedge clk) begin
    jump_valid_d1 <= jump_valid;
end

// pc control
always @* begin
    pc_next = pc;
    case (state)
        EXECUTE: begin
            if (execute_finish) begin
                if (jump_valid_d1) begin
                    pc_next = alu_result;
                end
                else begin
                    pc_next = pc + 4;
                end
            end
            else begin
                pc_next = pc;
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
                if (execute_finish) begin
                    state <= WRITEBACK;
                    if (jump_valid_d1) begin
                        jump_en(pc_next, pc, alu_result_rd, ((opcode==7'b1101111)? 'd0 : rs1));
                    end
                end
            end
            WRITEBACK: begin
                state <= FETCH;
            end
        endcase
    end
end

endmodule
