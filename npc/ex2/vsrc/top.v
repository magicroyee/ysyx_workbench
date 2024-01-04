module top(
    input [7:0] sws,
    output [3:0] leds,
    ouptut [7:0] seg
);
    
    wire en;
    wire [2:0] coded;

    code83 u_code83 (
        .x(sws),
        .en(en),
        .y(coded)
    );

    seg u_seg (
        .en(en),
        .data(coded),
        .seg(seg)
    );

    assign leds = {en, coded};

endmodule