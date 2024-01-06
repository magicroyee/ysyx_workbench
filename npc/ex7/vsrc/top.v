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
    output ready,
    output overflow,
    output [7:0] seg0,
    output [7:0] seg1,
    output [7:0] seg2,
    output [7:0] seg3,
    output [7:0] seg6,
    output [7:0] seg7
);

    wire [7:0] data;
    wire key_valid;
    wire [7:0] key_a;
    wire [7:0] key_c;
    wire [7:0] count;

    ps2_keyboard ps2_keyboard_inst(
        .clk(clk),
        .clrn(rstn),
        .ps2_clk(ps2_clk),
        .ps2_data(ps2_data),
        .data(data),
        .ready(ready),
        .nextdata_n(1'b0),
        .overflow(overflow)
    );

    code_analysis code_analysis_inst(
        .clk(clk),
        .rstn(rstn),
        .code_valid(ready),
        .code(data),
        .key_valid(key_valid),
        .key_a(key_a),
        .key_c(key_c),
        .count(count)
    );

    info_visual info_visual_inst(
        .clk(clk),
        .rstn(rstn),
        .key_valid(key_valid),
        .key_a(key_a),
        .key_c(key_c),
        .count(count),
        .seg0(seg0),
        .seg1(seg1),
        .seg2(seg2),
        .seg3(seg3),
        .seg6(seg6),
        .seg7(seg7)
    );

endmodule
