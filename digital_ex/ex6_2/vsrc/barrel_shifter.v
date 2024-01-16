module barrel_shifter (
    input clk,
    input rstn,
    input [7:0] din,
    input [2:0] shamt,
    input lr,
    input al,
    output reg [7:0] dout
);

    wire [31:0] shift;
    assign shift = {29'b0, shamt};
    integer i;
    always @(posedge clk or negedge rstn) begin
        if (!rstn) begin
            dout <= 8'b0;
        end
        else begin
            for (i=0; i<8; i=i+1) begin
                if (lr) begin
                    if (i < shamt) begin
                        dout[i] <= 1'b0;
                    end
                    else if (i < 7) begin
                        dout[i] <= din[i-shift];
                    end
                    else begin
                        dout[i] <= al? din[7] : 1'b0;
                    end
                end
                else begin
                    if (i < (8-shift)) begin
                        dout[i] <= din[i+shift];
                    end
                    else begin
                        dout[i] <= al? din[7] : 1'b0;
                    end
                end
            end
        end
    end

endmodule
