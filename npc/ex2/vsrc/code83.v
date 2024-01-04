module code83 (
    input [7:0]  x,
    output       en,
    output [2:0] y
);

integer i;

always @(*) begin
    if (!(|x)) begin
        en = 1'b0;
        y = 3'd0;
    end
    else begin
        en = 1'b0;
        y =  3'd0;
        for (i=0; i<=7; i=i+1) begin
            if (x[i]) begin
                en=1'b1;
                y=i[2:0];
            end
        end
    end
end

endmodule