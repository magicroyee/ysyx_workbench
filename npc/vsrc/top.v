`timescale 1ns / 1ps

module top(
    input clk,
    input rstn,
    output mem_rd,
    output [31:0] mem_raddr,
    input [31:0] mem_rdata
);

    ysyx_23060180_cpu_core cpu_core(
        .clk(clk),
        .rstn_in(rstn),
        .mem_rd(mem_rd),
        .mem_raddr(mem_raddr),
        .mem_rdata(mem_rdata)
    );

endmodule
