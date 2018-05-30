`timescale 1ns / 1ps

module CPU(
    input clk,
    input reset,
    output wire [31:0] pcAddressOutNext,
    output wire [31:0] pcAddressOut,
    output wire [31:0] imDataOut,
    output wire [31:0] rfReadData1,
    output wire [31:0] rfReadData2,
    output wire [31:0] rfWriteData,
    output wire [31:0] aluResult,
    output wire [31:0] dmDataOut
    );

    reg init;
    wire [31:0] tmp;

    wire [31:0] aluA, aluB;
    wire [31:0] imDataIn;
    wire [31:0] pcAddressIn, pcAddressOutPlus4, pcAddressOutPlus4PlusOffset;
    wire [31:0] extendResult;
    wire [4:0] rfWriteReg;
    wire [2:0] aluOp;
    wire [1:0] pcSelector;
    wire zero;
    wire dmReadOp, dmWriteOp, imReadWriteOp, rfWriteOp, pcWriteOp;
    wire aluASelector, aluBSelector, euSelector;
    wire rfWriteDataSelector, rfWriteRegSelector;

    assign pcAddressOutNext = (pcWriteOp == 1'B1 ? pcAddressIn : pcAddressOut);
    assign imDataIn = 32'B0;

    AddUnit pcPlus4(
        .a(32'H4),
        .b(pcAddressOut),
        .result(pcAddressOutPlus4)
    );

    AddUnit pcPlus4PlusOffset(
        .a(pcAddressOutPlus4),
        .b({ extendResult[29:0], 2'B0 }),
        .result(pcAddressOutPlus4PlusOffset)
    );

    ALUnit alu(
        .a(aluA),
        .b(aluB),
        .op(aluOp),
        .zero(zero),
        .result(aluResult)
    );

    ControlUnit cu(
        .op(imDataOut[31:26]),
        .zero(zero),
        .extend(euSelector),
        .PCSrcSelector(pcSelector),
        .PCWriteOp(pcWriteOp),
        .ALUSrcASelector(aluASelector),
        .ALUSrcBSelector(aluBSelector),
        .ALUOp(aluOp),
        .IMReadWriteOp(imReadWriteOp),
        .DMWriteOp(dmWriteOp),
        .DMReadOp(dmReadOp),
        .RFWriteRegSelector(rfWriteRegSelector),
        .RFWriteDataSelector(rfWriteDataSelector),
        .RFWriteOp(rfWriteOp)
    );

    DataMemory dm(
        .clk(clk),
        .readOp(dmReadOp),
        .writeOp(dmWriteOp),
        .address(aluResult),
        .dataIn(rfReadData2),
        .dataOut(dmDataOut)
    );

    ExtendUnit eu(
        .selector(euSelector),
        .dataIn(imDataOut[15:0]),
        .dataOut(extendResult)
    );

    InstructionMemory im(
        .readWriteOp(imReadWriteOp),
        .address(pcAddressOut),
        .dataIn(imDataIn),
        .dataOut(imDataOut)
    );

    ProgramCounter pc(
        .clk(clk),
        .reset(reset),
        .writeOp(pcWriteOp),
        .addressIn(pcAddressIn),
        .addressOut(pcAddressOut)
    );

    RegisterFile rf(
        .clk(clk),
        .init(init),
        .writeOp(rfWriteOp),
        .readReg1(imDataOut[25:21]),
        .readReg2(imDataOut[20:16]),
        .writeReg(rfWriteReg),
        .writeData(rfWriteData),
        .readData1(rfReadData1),
        .readData2(rfReadData2)
    );

    Selector2 aluSelectA(
        .selector(aluASelector),
        .dataIn0(rfReadData1),
        .dataIn1({ 27'B0, imDataOut[10:6] }),
        .dataOut(aluA)
    );

    Selector2 aluSelectB(
        .selector(aluBSelector),
        .dataIn0(rfReadData2),
        .dataIn1(extendResult),
        .dataOut(aluB)
    );

    Selector2 rfSelectWriteData(
        .selector(rfWriteDataSelector),
        .dataIn0(aluResult),
        .dataIn1(dmDataOut),
        .dataOut(rfWriteData)
    );

    Selector2 rfSelectWriteReg(
        .selector(rfWriteRegSelector),
        .dataIn0({ 27'B0, imDataOut[20:16] }),
        .dataIn1({ 27'B0, imDataOut[15:11] }),
        .dataOut({ tmp[31:5] , rfWriteReg })
    );

    Selector4 pcSelectAddress(
        .selector(pcSelector),
        .dataIn0(pcAddressOutPlus4),
        .dataIn1(pcAddressOutPlus4PlusOffset),
        .dataIn2({ pcAddressOutPlus4[31:28], imDataOut[25:0], 2'B0 }),
        .dataIn3(32'Bz),
        .dataOut(pcAddressIn)
    );

    initial begin
        init = 0;
    end

    always@(clk) begin
        if (init == 1'B0) begin
            init = 1;
        end
    end
endmodule
