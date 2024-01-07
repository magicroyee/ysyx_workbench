module code_analysis(
    input clk,
    input rstn,
    input code_valid,
    input [7:0] code,
    output reg key_valid,
    output reg [7:0] key_a,
    output reg [7:0] key_c,
    output [7:0] count
);

    reg [7:0] code_reg;
    reg       code_reg_valid;
    reg       releasing;
    reg [7:0] key_reg;
    reg       key_valid_d1;
    wire      new_key;
    reg [3:0] count0;
    reg [3:0] count1;

    always @(posedge clk or negedge rstn) begin
        if (!rstn) begin
            code_reg <= 8'h00;
        end
        else if(code_valid) begin
            code_reg <= code;
        end
    end

    always @(posedge clk or negedge rstn) begin
        if (!rstn) begin
            code_reg_valid <= 1'b0;
        end
        else begin
            code_reg_valid <= code_valid;
        end
    end

    always @(posedge clk or negedge rstn) begin
        if (!rstn) begin
            key_valid <= 1'b0;
        end
        else if(code_reg_valid) begin
            if (releasing && (code_reg == key_reg)) begin
                key_valid <= 1'b0;
            end
            else if (code_reg_valid && ~releasing && code_reg != 8'hf0) begin
                key_valid <= 1'b1;
            end
        end
    end

    always @(posedge clk or negedge rstn) begin
        if (!rstn) begin
            releasing <= 1'b0;
        end
        else if(code_reg_valid) begin
            if (code_reg == 8'hf0) begin
                releasing <= 1'b1;
            end
            else if (releasing) begin
                releasing <= 1'b0;
            end
        end
    end

    reg [7:0] key_c2a_mem [0:255];
    initial begin
        $readmemh("resources/key_c2a.mem", key_c2a_mem);
    end

    always @(posedge clk or negedge rstn) begin
        if (!rstn) begin
            key_a <= 8'h00;
        end
        else if(code_reg_valid) begin
            if (code_reg != 8'hf0) begin
                key_a <= key_c2a_mem[code_reg];
            end
        end
    end

    always @(posedge clk or negedge rstn) begin
        if (!rstn) begin
            key_c <= 8'h00;
        end
        else if(code_reg_valid) begin
            if ((code_reg != 8'hf0) && ~releasing) begin
                key_c <= code_reg;
            end
        end
    end

    always @(posedge clk or negedge rstn) begin
        if (!rstn) begin
            key_reg <= 8'h00;
        end
        else if(code_reg_valid) begin
            if ((code_reg != 8'hf0) && ~releasing) begin
                key_reg <= code_reg;
            end
        end
    end

    always @(posedge clk or negedge rstn) begin
        if (!rstn) begin
            key_valid_d1 <= 1'b0;
        end
        else begin
            key_valid_d1 <= key_valid;
        end
    end

    // assign new_key = (key_valid & ~key_valid_d1) | (key_valid & (code_reg != 8'hf0) & (code_reg != key_reg) & ~releasing);
    assign new_key = (key_valid & ~key_valid_d1) | (key_valid & code_reg_valid & (code_reg != 8'hf0) & (code_reg != key_reg) & ~releasing);

    always @(posedge clk or negedge rstn) begin
        if (!rstn) begin
            count0 <= 4'h0;
        end
        else if(new_key) begin
            if (count0 < 4'h9) begin
                count0 <= count0 + 4'h1;
            end
            else begin
                count0 <= 4'h0;
            end
        end
    end

    always @(posedge clk or negedge rstn) begin
        if (!rstn) begin
            count1 <= 4'h0;
        end
        else if(new_key && (count0 == 4'h9)) begin
            if (count1 < 4'h9) begin
                count1 <= count1 + 4'h1;
            end
            else begin
                count1 <= 4'h0;
            end
        end
    end

    assign count = {count1, count0};

endmodule
