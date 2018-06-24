`timescale 1ns / 1ps

module ControlUnit(
    input [5:0] op,
    input clk,
    input rst,
    input zero,
    input sign,

    output wire [2:0] state,

    output ExtSel,

    // PC
    output [1:0] PCSrc,
    output PCWre,

    // ALU
    output ALUSrcA,
    output ALUSrcB,
    output reg [2:0] ALUOp,

    // Instruction Memory
    output InsMemRW,
    output IRWre,

    // Data Memory
    output mRD,
    output mWR,
    output DBDataSrc,

    // Register File
    output RegWre,
    output WrRegDSrc,
    output [1:0] RegDst
    );

    MultiState ms(
        .clk(clk),
        .rst(rst),
        .op(op),
        .state(state)
    );

    assign PCWre = (op != 6'B111111 && state == 3'B000 ? 1 : 0);
    assign ALUSrcA = (op == 6'B011000 ? 1 : 0);
    assign ALUSrcB = (op == 6'B000010 || op == 6'B010010 || op == 6'B100111
        || op == 6'B110000 || op == 6'B110001 ? 1 : 0);
    assign DBDataSrc = (op == 6'B110001 ? 1 : 0);
    assign RegWre = (op == 6'B110100 || op == 6'B110110 || op == 6'B111000
        || op == 6'B110000 || op == 6'B111001 || op == 6'B111111 || (state != 3'B011 && op != 6'B111010) ? 0 : 1);
    assign WrRegDSrc = (op != 6'B111010 ? 1 : 0);
    assign InsMemRW = 1;
    assign mRD = (op == 6'B110001 && state == 3'B100 ? 1 : 0);
    assign mWR = (op == 6'B110000 && state == 3'B100 ? 1 : 0);
    assign IRWre = (state == 3'B000 ? 1 : 0);
    assign ExtSel = (op != 6'B010010 && op != 6'B100111 ? 1 : 0);
    assign PCSrc = (op == 6'B111000 || op == 6'B111010 ? 2'B11 :
        (op == 6'B111001 ? 2'B10 :
        ((op == 6'B110100 && zero == 1) || (op == 6'B110110 && (sign == 1 && zero == 0)) ? 2'B01 :
        2'B00)));
    assign RegDst = (op == 6'B111010 ? 2'B00 :
        (op == 6'B000010 || op == 6'B010010 || op == 6'B100111 || op == 6'B110001 ? 2'B01 : 2'B10));

    always@(op or zero or sign) begin
        case (op)
            // add
            6'B000000: ALUOp = 3'B000;
            // sub
            6'B000001: ALUOp = 3'B001;
            // addi
            6'B000010: ALUOp = 3'B000;
            // or
            6'B010000: ALUOp = 3'B101;
            // and
            6'B010001: ALUOp = 3'B110;
            // ori
            6'B010010: ALUOp = 3'B101;
            // sll
            6'B011000: ALUOp = 3'B100;
            // slt
            6'B100110: ALUOp = 3'B011;
            // sltiu
            6'B100111: ALUOp = 3'B010;
            // sw
            6'B110000: ALUOp = 3'B000;
            // lw
            6'B110001: ALUOp = 3'B000;
            // beq
            6'B110100: ALUOp = 3'B001;
            // bltz
            6'B110110: ALUOp = 3'B001;
            // j
            6'B111000: ALUOp = 3'Bzzz;
            // jr
            6'B111001: ALUOp = 3'Bzzz;
            // jal
            6'B111010: ALUOp = 3'Bzzz;
            // halt
            6'B111111: ALUOp = 3'Bzzz;
        endcase
    end
endmodule
