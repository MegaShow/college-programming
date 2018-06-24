`timescale 1ns / 1ps

module InstructionRegister(
    input clk,
    input IRWre,
    input [31:0] dataIn,
    output reg [31:0] dataOut
    );

    always@(posedge clk) begin
        if (IRWre == 1) begin
            dataOut = dataIn;
        end
    end

endmodule
