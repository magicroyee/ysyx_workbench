module info_visual(
    input clk,
    input rstn,
    input key_valid,
    input [7:0] key_a,
    input [7:0] key_c,
    input [7:0] count,
    output [7:0] seg0,
    output [7:0] seg1,
    output [7:0] seg2,
    output [7:0] seg3,
    output [7:0] seg6,
    output [7:0] seg7
);

    seg seg0_inst(
        .en(key_valid),
        .data(key_c[3:0]),
        .seg(seg0)
    );

    seg seg1_inst(
        .en(key_valid),
        .data(key_c[7:4]),
        .seg(seg1)
    );

    seg seg2_inst(
        .en(key_valid),
        .data(key_a[3:0]),
        .seg(seg2)
    );

    seg seg3_inst(
        .en(key_valid),
        .data(key_a[7:4]),
        .seg(seg3)
    );

    seg seg6_inst(
        .en(1'b1),
        .data(count[3:0]),
        .seg(seg6)
    );

    seg seg7_inst(
        .en(1'b1),
        .data(count[7:4]),
        .seg(seg7)
    );

endmodule