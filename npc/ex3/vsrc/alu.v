module alu (
    input [3:0] a,
    input [3:0] b,
    input [2:0] op,
    output reg [3:0] y,
    output reg c,
    output reg z,
    output reg of
);
    reg [4:0] tmp;
    reg [3:0] nb_nocin;
    // a,b are signed numbers
    always @(*) begin
        nb_nocin = ~b;
        tmp = 5'd0;
        y = 4'd0;
        c = 1'b0;
        z = 1'b0;
        of = 1'b0;
        case(op)
        3'b000: begin
            tmp = a + b;
            y = tmp[3:0];
            c = tmp[4];
            z = ~(|y);
            of = (a[3] == b[3]) && (y[3] != a[3]);
        end
        3'b001: begin
            tmp = a + nb_nocin + 1'b1;
            y = tmp[3:0];
            c = tmp[4];
            z = ~(|y);
            of = (a[3] == nb_nocin[3]) && (y[3] != a[3]);
        end
        3'b010: begin
            y = ~a;
            z = ~(|y);
        end
        3'b011: begin
            y = a & b;
            z = ~(|y);
        end
        3'b100: begin
            y = a | b;
            z = ~(|y);
        end
        3'b101: begin
            y = a ^ b;
            z = ~(|y);
        end
        3'b110: begin
            if (a[3] != b[3]) begin
                y[0] = a > b;
            end
            else begin
                y[0] = a < b;
            end
            z = ~(|y);
        end
        3'b111: begin
            y[0] = a == b;
            z = ~(|y);
        end
        endcase
    end
endmodule
