`timescale 1ns / 1ps

module ALUnit(
    input [31:0] a,
    input [31:0] b,
    input [2:0] op,
    output zero,
    output reg [31:0] result
    );

    assign zero = (result == 0 ? 1'B1 : 1'B0);

    always@(a or b or op) begin
        case(op)
            3'B000: result = a + b;
            3'B001: result = a - b;
            3'B010: result = a[31] == 1'B0 ? b << a : b >> (~a + 1);
            3'B011: result = a | b;
            3'B100: result = a & b;
            3'B101: result = a < b ? 1 : 0;
            3'B110: result = (a[31] == b[31] && a < b) || (a[31] == 1'B1 && b[31] == 1'B0) ? 1 : 0;
            3'B111: result = a ^ b;
        endcase
    end

endmodule
