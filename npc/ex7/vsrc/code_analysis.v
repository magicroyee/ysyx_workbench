module code_analysis(
    input clk,
    input rstn,
    input code_valid,
    input [7:0] code,
    output reg key_valid,
    output reg [7:0] key_a,
    output reg [7:0] key_c,
    output reg [7:0] count
);

    reg [7:0] code_reg;
    reg       code_reg_valid;
    reg       releasing;
    reg [7:0] key_reg;
    reg       key_valid_d1;
    wire      new_key;

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
            else if (code_reg != 8'hf0) begin
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
    assign new_key = (key_valid & ~key_valid_d1) | (key_valid & (code_reg != 8'hf0) & (code_reg != key_reg) & ~releasing);

    always @(posedge clk or negedge rstn) begin
        if (!rstn) begin
            count <= 8'h00;
        end
        else if(new_key) begin
            count <= count + 8'h01;
        end
    end

endmodule