`timescale 1ns / 1ps

module DataMemory(
    input readOp,
    input writeOp,
    input [31:0] address,
    input [31:0] dataIn,
    output [31:0] dataOut
    );

    reg [7:0] ram [0:127];

    assign dataOut[31:24] = (readOp == 1'B1 ? ram[address] : 8'Bz);
    assign dataOut[23:16] = (readOp == 1'B1 ? ram[address + 1] : 8'Bz);
    assign dataOut[15:8] = (readOp == 1'B1 ? ram[address + 2] : 8'Bz);
    assign dataOut[7:0] = (readOp == 1'B1 ? ram[address + 3] : 8'Bz);

    always@(writeOp) begin
        if (writeOp == 1'B1) begin
            ram[address] <= dataIn[31:24];
            ram[address + 1] <= dataIn[23:16];
            ram[address + 2] <= dataIn[15:8];
            ram[address + 3] <= dataIn[7:0];
        end
    end
endmodule
