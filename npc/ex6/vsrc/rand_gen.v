module rand_gen (
    input clk,
    input rstn,
    output reg [7:0] x
);

    wire x8 = x[4] ^ x[3] ^ x[2] ^ x[0];
    always @(posedge clk or negedge rstn) begin
        if (!rstn) begin
            x <= 8'b00000001;
        end
        else begin
            x <= {x8, x[7:1]};
        end
    end
    
endmodule
