`timescale 1ns / 1ps

module RegisterFileSim();
    reg clk;
    reg init;
    reg [4:0] readReg1;
    reg [4:0] readReg2;
    reg [4:0] writeReg;
    reg writeOp;
    reg [31:0] writeData;

    wire [31:0] readData1;
    wire [31:0] readData2;

    RegisterFile file(
        .clk(clk),
        .init(init),
        .writeOp(writeOp),
        .readReg1(readReg1),
        .readReg2(readReg2),
        .writeReg(writeReg),
        .writeData(writeData),
        .readData1(readData1),
        .readData2(readData2)
    );

    always #50 clk = ~clk;

    initial begin
        clk = 0;
        init = 0;
        writeOp = 0;
        readReg1 = 0;
        readReg2 = 0;
        writeReg = 0;
        writeData = 0;

        // write $1 = 1
        #100
        init = 1;
        writeOp = 1;
        readReg1 = 0;
        readReg2 = 0;
        writeReg = 1;
        writeData = 1;

        // write $2 = 2
        #100
        init = 1;
        writeOp = 1;
        readReg1 = 0;
        readReg2 = 0;
        writeReg = 2;
        writeData = 2;

        // write $3 = 3
        #100
        init = 1;
        writeOp = 1;
        readReg1 = 0;
        readReg2 = 0;
        writeReg = 3;
        writeData = 3;

        // read1 $1 == 1
        #100
        init = 1;
        writeOp = 0;
        readReg1 = 1;
        readReg2 = 0;
        writeReg = 0;
        writeData = 0;

        // read2 $2 == 2
        #100
        init = 1;
        writeOp = 0;
        readReg1 = 0;
        readReg2 = 2;
        writeReg = 0;
        writeData = 0;

        // read1 $1 == 1, read2 $3 == 3
        #100
        init = 1;
        writeOp = 0;
        readReg1 = 1;
        readReg2 = 3;
        writeReg = 0;
        writeData = 0;

        #200

        // reset
        #100
        init = 0;
        writeOp = 0;
        readReg1 = 0;
        readReg2 = 0;
        writeReg = 0;
        writeData = 0;
    end

endmodule
