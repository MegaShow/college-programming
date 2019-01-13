`timescale 1ns / 1ps

module DataMemorySim();
    reg clk;
    reg readOp;
    reg writeOp;
    reg [31:0] address;
    reg [31:0] dataIn;

    wire [31:0] dataOut;

    DataMemory ram(
        .clk(clk),
        .readOp(readOp),
        .writeOp(writeOp),
        .address(address),
        .dataIn(dataIn),
        .dataOut(dataOut)
    );

    always #15 clk = ~clk;

    initial begin
        clk = 0;
        address = 0;
        dataIn = 0;
        readOp = 0;
        writeOp = 0;

        // write
        #30
        address = 8;
        dataIn = 8;
        readOp = 0;
        writeOp = 1;

        // write
        #30
        address = 12;
        dataIn = 12;
        readOp = 0;
        writeOp = 1;

        // read
        #30
        address = 8;
        readOp = 1;
        writeOp = 0;

        // read
        #30
        address = 12;
        readOp = 1;
        writeOp = 0;

        // reset
        #30
        address = 0;
        dataIn = 0;
        readOp = 0;
        writeOp = 0;
    end
endmodule
