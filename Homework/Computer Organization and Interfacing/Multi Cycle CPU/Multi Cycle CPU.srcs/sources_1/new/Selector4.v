`timescale 1ns / 1ps

module Selector4(
    input [1:0] selector,
    input [31:0] dataIn0,
    input [31:0] dataIn1,
    input [31:0] dataIn2,
    input [31:0] dataIn3,
    output [31:0] dataOut
    );

    assign dataOut = (selector == 2'B00 ? dataIn0 :
        (selector == 2'B01 ? dataIn1 :
        (selector == 2'B10 ? dataIn2 : dataIn3)));
endmodule
