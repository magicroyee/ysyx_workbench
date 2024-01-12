module top(
    input clk,
    input rstn,
    output [7:0] x
);
    
    rand_gen u_rand_gen(
        .clk  	( clk   ),
        .rstn 	( rstn  ),
        .x    	( x     )
    );

endmodule
