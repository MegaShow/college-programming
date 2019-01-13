`timescale 1ns / 1ps

module CPUSim();
    reg clk;
    reg reset;
    wire [31:0] pc, pcNext;
    wire [2:0] state;
    wire [31:0] instruction;
    wire [31:26] op;
    wire [25:21] rs;
    wire [20:16] rt;
    wire [15:11] rd;
    wire [10:6] sa;
    wire [15:0] imm;
    wire [25:0] address;
    wire [31:0] readData1, readData2, writeData, aluResult, memData;

    assign op = instruction[31:26];
    assign rs = instruction[25:21];
    assign rt = instruction[20:16];
    assign rd = instruction[15:11];
    assign sa = instruction[10:6];
    assign imm = instruction[15:0];
    assign address = instruction[25:0];

    CPU cpu(
        .clk(clk),
        .reset(reset),
        .state(state),
        .pcAddressOutNext(pcNext),
        .pcAddressOut(pc),
        .imDataOut(instruction),
        .rfReadData1(readData1),
        .rfReadData2(readData2),
        .dbdrDataOut(writeData),
        .aluResult(aluResult),
        .dmDataOut(memData)
    );

    always #15 clk = ~clk;

    initial begin
        clk = 0;
        reset = 0;

        #45
        reset = 1;
    end
endmodule
