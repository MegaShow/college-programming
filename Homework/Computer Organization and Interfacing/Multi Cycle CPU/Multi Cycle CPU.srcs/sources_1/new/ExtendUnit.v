`timescale 1ns / 1ps

module ExtendUnit(
    input selector,
    input [15:0] dataIn,
    output [31:0] dataOut
    );

    assign dataOut = (selector == 1'B0 || dataIn[15] == 1'B0
        ? { 16'B0, dataIn } : { 16'HFFFF, dataIn });
endmodule
