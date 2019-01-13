`timescale 1ns / 1ps

module ProgramCounter(
    input clk,
    input reset,
    input writeOp,
    input [31:0] addressIn,
    output reg [31:0] addressOut
    );

    reg init;

    initial begin
        addressOut <= 0;
        init <= 0;
    end

    always@(posedge clk) begin
        if (init == 1'B0) begin
            init = 1;
        end else if (reset == 1'B0) begin
            addressOut = 0;
        end else if (writeOp == 1'B1) begin
            addressOut = addressIn;
        end
    end
endmodule
