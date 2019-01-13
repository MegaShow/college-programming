`timescale 1ns / 1ps

module DataRegister(
    input clk,
    input [31:0] dataIn,
    output reg [31:0] dataOut
    );

    always@(negedge clk) begin
        dataOut = dataIn;
    end

endmodule
