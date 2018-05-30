`timescale 1ns / 1ps

module ControlUnit(
    input [5:0] op,
    input zero,
    output reg extend,

    // PC
    output reg [1:0] PCSrcSelector,
    output reg PCWriteOp,

    // ALU
    output reg ALUSrcASelector,
    output reg ALUSrcBSelector,
    output reg [2:0] ALUOp,

    // Instruction Memory
    output reg IMReadWriteOp,

    // Data Memory
    output reg DMWriteOp,
    output reg DMReadOp,

    // Register File
    output reg RFWriteRegSelector,
    output reg RFWriteDataSelector,
    output reg RFWriteOp
    );

    initial begin
        extend = 0;
        PCSrcSelector = 2'B00;
        PCWriteOp = 0;
        ALUSrcASelector = 0;
        ALUSrcBSelector = 0;
        ALUOp = 3'B000;
        IMReadWriteOp = 1;
        DMWriteOp = 0;
        DMReadOp = 0;
        RFWriteRegSelector = 0;
        RFWriteDataSelector = 0;
        RFWriteOp = 0;
    end

    always@(op or zero) begin
        case (op)
            // add rd, rs, rt
            6'B000000: begin
                // extend = 0;
                PCSrcSelector = 2'B00;
                PCWriteOp = 1;
                ALUSrcASelector = 0;
                ALUSrcBSelector = 0;
                ALUOp = 3'B000;
                IMReadWriteOp = 1;
                DMWriteOp = 0;
                DMReadOp = 0;
                RFWriteRegSelector = 1;
                RFWriteDataSelector = 0;
                RFWriteOp = 1;
            end

            // addi rt, rs, imm
            6'B000001: begin
                extend = 1;
                PCSrcSelector = 2'B00;
                PCWriteOp = 1;
                ALUSrcASelector = 0;
                ALUSrcBSelector = 1;
                ALUOp = 3'B000;
                IMReadWriteOp = 1;
                DMWriteOp = 0;
                DMReadOp = 0;
                RFWriteRegSelector = 0;
                RFWriteDataSelector = 0;
                RFWriteOp = 1;
            end

            // sub rd, rs, rt
            6'B000010: begin
                // extend = 0;
                PCSrcSelector = 2'B00;
                PCWriteOp = 1;
                ALUSrcASelector = 0;
                ALUSrcBSelector = 0;
                ALUOp = 3'B001;
                IMReadWriteOp = 1;
                DMWriteOp = 0;
                DMReadOp = 0;
                RFWriteRegSelector = 1;
                RFWriteDataSelector = 0;
                RFWriteOp = 1;
            end

            // ori rt, rs, imm
            6'B010000: begin
                extend = 0;
                PCSrcSelector = 2'B00;
                PCWriteOp = 1;
                ALUSrcASelector = 0;
                ALUSrcBSelector = 1;
                ALUOp = 3'B011;
                IMReadWriteOp = 1;
                DMWriteOp = 0;
                DMReadOp = 0;
                RFWriteRegSelector = 0;
                RFWriteDataSelector = 0;
                RFWriteOp = 1;
            end

            // and rd, rs, rt
            6'B010001: begin
                // extend = 0;
                PCSrcSelector = 2'B00;
                PCWriteOp = 1;
                ALUSrcASelector = 0;
                ALUSrcBSelector = 0;
                ALUOp = 3'B100;
                IMReadWriteOp = 1;
                DMWriteOp = 0;
                DMReadOp = 0;
                RFWriteRegSelector = 1;
                RFWriteDataSelector = 0;
                RFWriteOp = 1;
            end

            // or rd, rs, rt
            6'B010010: begin
                // extend = 0;
                PCSrcSelector = 2'B00;
                PCWriteOp = 1;
                ALUSrcASelector = 0;
                ALUSrcBSelector = 0;
                ALUOp = 3'B011;
                IMReadWriteOp = 1;
                DMWriteOp = 0;
                DMReadOp = 0;
                RFWriteRegSelector = 1;
                RFWriteDataSelector = 0;
                RFWriteOp = 1;
            end

            // sll rd, rt, sa
            6'B011000: begin
                // extend = 0;
                PCSrcSelector = 2'B00;
                PCWriteOp = 1;
                ALUSrcASelector = 1;
                ALUSrcBSelector = 0;
                ALUOp = 3'B010;
                IMReadWriteOp = 1;
                DMWriteOp = 0;
                DMReadOp = 0;
                RFWriteRegSelector = 1;
                RFWriteDataSelector = 0;
                RFWriteOp = 1;
            end

            // slti rt, rs, imm
            6'B011011: begin
                extend = 1;
                PCSrcSelector = 2'B00;
                PCWriteOp = 1;
                ALUSrcASelector = 0;
                ALUSrcBSelector = 1;
                ALUOp = 3'B110;
                IMReadWriteOp = 1;
                DMWriteOp = 0;
                DMReadOp = 0;
                RFWriteRegSelector = 0;
                RFWriteDataSelector = 0;
                RFWriteOp = 1;
            end

            // sw rt, imm(rs)
            6'B100110: begin
                extend = 1;
                PCSrcSelector = 2'B00;
                PCWriteOp = 1;
                ALUSrcASelector = 0;
                ALUSrcBSelector = 1;
                ALUOp = 3'B000;
                IMReadWriteOp = 1;
                DMWriteOp = 1;
                DMReadOp = 0;
                RFWriteRegSelector = 1;
                // RFWriteDataSelector = 0;
                RFWriteOp = 0;
            end

            // lw rt, imm(rs)
            6'B100111: begin
                extend = 1;
                PCSrcSelector = 2'B00;
                PCWriteOp = 1;
                ALUSrcASelector = 0;
                ALUSrcBSelector = 1;
                ALUOp = 3'B000;
                IMReadWriteOp = 1;
                DMWriteOp = 0;
                DMReadOp = 1;
                RFWriteRegSelector = 0;
                RFWriteDataSelector = 1;
                RFWriteOp = 1;
            end

            // beq rs, rt, imm
            6'B110000: begin
                extend = 1;
                PCSrcSelector = (zero == 0 ? 2'B00 : 2'B01);
                PCWriteOp = 1;
                ALUSrcASelector = 0;
                ALUSrcBSelector = 0;
                ALUOp = 3'B001;
                IMReadWriteOp = 1;
                DMWriteOp = 0;
                DMReadOp = 0;
                RFWriteRegSelector = 1;
                // RFWriteDataSelector = 0;
                RFWriteOp = 0;
            end

            // bne rs, rt, imm
            6'B110001: begin
                extend = 1;
                PCSrcSelector = (zero == 1 ? 2'B00 : 2'B01);
                PCWriteOp = 1;
                ALUSrcASelector = 0;
                ALUSrcBSelector = 0;
                ALUOp = 3'B001;
                IMReadWriteOp = 1;
                DMWriteOp = 0;
                DMReadOp = 0;
                RFWriteRegSelector = 1;
                // RFWriteDataSelector = 0;
                RFWriteOp = 0;
            end

            // j addr
            6'B111000: begin
                // extend = 0;
                PCSrcSelector = 2'B10;
                PCWriteOp = 1;
                // ALUSrcASelector = 0;
                // ALUSrcBSelector = 0;
                // ALUOp = 3'B000;
                IMReadWriteOp = 1;
                DMWriteOp = 0;
                DMReadOp = 0;
                // RFWriteRegSelector = 1;
                // RFWriteDataSelector = 0;
                RFWriteOp = 0;
            end

            // halt
            6'B111111: begin
                // extend = 0;
                // PCSrcSelector = 2'B00;
                PCWriteOp = 0;
                // ALUSrcASelector = 0;
                // ALUSrcBSelector = 0;
                // ALUOp = 3'B000;
                IMReadWriteOp = 1;
                DMWriteOp = 0;
                DMReadOp = 0;
                // RFWriteRegSelector = 1;
                // RFWriteDataSelector = 0;
                RFWriteOp = 0;
            end
        endcase
    end
endmodule
