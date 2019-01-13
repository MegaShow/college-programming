`timescale 1ns / 1ps

module InstructionMemory(
    input readWriteOp,            // 0 => write, 1 => read
    input [31:0] address,
    input [31:0] dataIn,
    output reg [31:0] dataOut
    );

    reg [7:0] ram [0:127];

    initial begin
        $readmemh("C:/Users/MegaX/Desktop/Single Cycle CPU/Single Cycle CPU.srcs/img.txt", ram);
    end

    always@(address or readWriteOp) begin
        if (readWriteOp == 1'B1) begin
            dataOut[31:24] = ram[address];
            dataOut[23:16] = ram[address + 1];
            dataOut[15:8] = ram[address + 2];
            dataOut[7:0] = ram[address + 3];
        end
    end
endmodule
