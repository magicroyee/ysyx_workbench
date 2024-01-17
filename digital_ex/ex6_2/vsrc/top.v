module top(
    input clk,
    input rstn,
    input [7:0] din,
    input [2:0] shamt,
    input lr,
    input al,
    output [7:0] dout
);

    barrel_shifter u_barrel_shifter (
        .clk(clk),
        .rstn(rstn),
        .din(din),
        .shamt(shamt),
        .lr(lr),
        .al(al),
        .dout(dout)
    );

endmodule
