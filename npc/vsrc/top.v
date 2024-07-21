`timescale 1ns / 1ps

module top(
    input clk,
    input rstn,
    output mem_rd,
    output mem_wr,
    output [31:0] mem_raddr,
    input [31:0] mem_rdata,
    output [31:0] mem_wdata,
    output [3:0] mem_wbit_en
);

    ysyx_23060180_cpu_core cpu_core(
        .clk(clk),
        .rstn_in(rstn),
        .mem_rd(mem_rd),
        .mem_wr(mem_wr),
        .mem_raddr(mem_raddr),
        .mem_rdata(mem_rdata),
        .mem_wdata(mem_wdata),
        .mem_wbit_en(mem_wbit_en)
    );

endmodule
