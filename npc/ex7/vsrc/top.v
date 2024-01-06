// module ps2_keyboard(clk,clrn,ps2_clk,ps2_data,data,
//                     ready,nextdata_n,overflow);
//     input clk,clrn,ps2_clk,ps2_data;
//     input nextdata_n;
//     output [7:0] data;
//     output reg ready;
//     output reg overflow;     // fifo overflow
module top(
    input clk,
    input rstn,
    input ps2_clk,
    input ps2_data,
    output [7:0] data,
    output ready,
    output nextdata_n,
    output overflow
);

    ps2_keyboard inst(
        .clk(clk),
        .clrn(rstn),
        .ps2_clk(ps2_clk),
        .ps2_data(ps2_data),
        .data(data),
        .ready(ready),
        .nextdata_n(nextdata_n),
        .overflow(overflow)
    );


endmodule
