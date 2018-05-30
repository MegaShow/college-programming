`timescale 1ns / 1ps

module AddUnit(
    input [31:0] a,
    input [31:0] b,
    output [31:0] result
    );

    assign result = a + b;
endmodule
