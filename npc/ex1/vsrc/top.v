module top(
    input [1:0] y,
    input [1:0] x0,
    input [1:0] x1,
    input [1:0] x2,
    input [1:0] x3,
    output [1:0] f
);
    
    wire [15:0] lut;
    assign lut[3:0] = {2'b00, x0};
    assign lut[7:4] = {2'b01, x1};
    assign lut[11:8] = {2'b10, x2};
    assign lut[15:12] = {2'b11, x3};

    MuxKey #(4, 2, 2) i0 (
        .out(f),
        .key(y),
        .lut(lut)
    );

endmodule