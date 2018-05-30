`timescale 1ns / 1ps

module Selector2(
    input selector,
    input [31:0] dataIn0,
    input [31:0] dataIn1,
    output [31:0] dataOut
    );

    assign dataOut = (selector == 1'B0 ? dataIn0 : dataIn1);
endmodule
