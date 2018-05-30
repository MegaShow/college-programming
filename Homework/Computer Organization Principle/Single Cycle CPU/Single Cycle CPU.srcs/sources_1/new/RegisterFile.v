`timescale 1ns / 1ps

module RegisterFile(
    input clk,
    input init,
    input writeOp,
    input [4:0] readReg1,
    input [4:0] readReg2,
    input [4:0] writeReg,
    input [31:0] writeData,
    output [31:0] readData1,
    output [31:0] readData2
    );

    reg [31:0] regData[1:31];
    integer i;

    assign readData1 = readReg1 == 0 ? 0 : regData[readReg1];
    assign readData2 = readReg2 == 0 ? 0 : regData[readReg2];

    always@(negedge clk or negedge init) begin
        if (init == 1'B0) begin
            for (i = 1; i < 32; i = i + 1) begin
                regData[i] <= 0;
            end
        end else if (writeOp == 1'B1 && writeReg != 0) begin
            regData[writeReg] <= writeData;
        end
    end

endmodule
