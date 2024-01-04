module seg (
    input en,
    input [2:0] data,
    output reg [7:0] seg
);

    always @(*) begin
        if (!en) begin
            seg = 8'b11111111;
        end
        else begin
            case(data)
            3'd0: seg = 8'b00000011;
            3'd1: seg = 8'b10011111;
            3'd2: seg = 8'b00100101;
            3'd3: seg = 8'b00001101;
            3'd4: seg = 8'b10011001;
            3'd5: seg = 8'b01001001;
            3'd6: seg = 8'b01000001;
            3'd7: seg = 8'b00011111;
            default: seg = 8'b11111111;
            endcase
        end
    end

endmodule