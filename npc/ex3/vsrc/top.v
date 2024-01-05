module top(
    input [3:0] a,
    input [3:0] b,
    input [2:0] op,
    output [3:0] y,
    output c,
    output z,
    output of
);
    
    alu u_alu (
        .a(a),
        .b(b),
        .op(op),
        .y(y),
        .c(c),
        .z(z),
        .of(of)
    );

endmodule