module top(
    input clk,
    input rstn,
    input a,
    input b,
    output reg f
);
    always @(posedge clk or negedge rstn) begin
        if (!rstn) begin
            f <= 1'b0;
        end else begin
            f <= a ^ b;
        end
    end

endmodule
