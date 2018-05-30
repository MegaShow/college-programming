`timescale 1ns / 1ps

module Basys3(
    input [1:0] switch,
    input mclk,
    input btnClk,
    input reset,
    output wire [7:0] display,
    output wire [3:0] an
    );

    reg [15:0] tmp[0:3];
    reg [15:0] num;
    wire clk;

    wire [31:0] pc, pcNext;
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
        .pcAddressOutNext(pcNext),
        .pcAddressOut(pc),
        .imDataOut(instruction),
        .rfReadData1(readData1),
        .rfReadData2(readData2),
        .rfWriteData(writeData),
        .aluResult(aluResult),
        .dmDataOut(memData)
    );

    Print print(
        .mclk(mclk),
        .num(num),
        .display(display),
        .an(an)
    );

    Button btn(
        .mclk(mclk),
        .in(btnClk),
        .out(clk)
    );

    always@(switch or pcNext or pc or instruction or readData1 or readData2 or aluResult or writeData) begin
        case (switch)
            2'B00: num = { pc[7:0], pcNext[7:0] };
            2'B01: num = { 3'B0, instruction[25:21], readData1[7:0] };
            2'B10: num = { 3'B0, instruction[20:16], readData2[7:0] };
            2'B11: num = { aluResult[7:0], writeData[7:0] };
        endcase
    end
endmodule
