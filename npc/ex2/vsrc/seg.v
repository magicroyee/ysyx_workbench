module seg (
    input en,
    input [2:0] data,
    output reg [7:0] seg
);

    always @(*) begin
        if (!en) begin
            seg = 8'b00000000;
        end
        else begin
            case(data)
            3'd0: seg = 8'b11111100;
            3'd1: seg = 8'b01100000;
            3'd2: seg = 8'b11011010;
            3'd3: seg = 8'b11110010;
            3'd4: seg = 8'b01100110;
            3'd5: seg = 8'b10110110;
            3'd6: seg = 8'b10111110;
            3'd7: seg = 8'b11100000;
            endcase
        end
    end

endmodule