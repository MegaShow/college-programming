`timescale 1ns / 1ps

module CPU(
    input clk,
    input reset,
    output wire [2:0] state,
    output wire [31:0] pcAddressOutNext,
    output wire [31:0] pcAddressOut,
    output wire [31:0] imDataOut,
    output wire [31:0] rfReadData1,
    output wire [31:0] rfReadData2,
    output wire [31:0] dbdrDataOut,
    output wire [31:0] aluResult,
    output wire [31:0] dmDataOut
    );

    reg init;
    wire [31:0] tmp;

    wire [31:0] aluA, aluB;
    wire [31:0] imDataIn, imDataOut, instruction;
    wire [31:0] pcAddressIn, pcAddressOutPlus4, pcAddressOutPlus4PlusOffset;
    wire [31:0] extendResult;
    wire [31:0] rfWriteData;
    wire [4:0] rfWriteReg;

    wire [31:0] aluoutdrDataOut, dbdrDataIn, adrDataOut, bdrDataOut;

    wire zero, sign;
    wire ExtSel;
    wire [1:0] PCSrc;
    wire PCWre;
    wire ALUSrcA, ALUSrcB;
    wire [2:0] ALUOp;
    wire InsMemRW, IRWre, mRD, mWR, DBDataSrc;
    wire RegWre, WrRegDSrc;
    wire [1:0] RegDst;

    assign pcAddressOutNext = (instruction[31:26] == 6'B111111 ? pcAddressOut : pcAddressIn);
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
        .op(ALUOp),
        .zero(zero),
        .sign(sign),
        .result(aluResult)
    );

    ControlUnit cu(
        .op(instruction[31:26]),
        .clk(clk),
        .rst(reset),
        .state(state),
        .zero(zero),
        .sign(sign),
        .ExtSel(ExtSel),
        .PCSrc(PCSrc),
        .PCWre(PCWre),
        .ALUSrcA(ALUSrcA),
        .ALUSrcB(ALUSrcB),
        .ALUOp(ALUOp),
        .InsMemRW(InsMemRW),
        .IRWre(IRWre),
        .mRD(mRD),
        .mWR(mWR),
        .DBDataSrc(DBDataSrc),
        .RegWre(RegWre),
        .WrRegDSrc(WrRegDSrc),
        .RegDst(RegDst)
    );

    DataMemory dm(
        .readOp(mRD),
        .writeOp(mWR),
        .address(aluoutdrDataOut),
        .dataIn(bdrDataOut),
        .dataOut(dmDataOut)
    );

    DataRegister adr(
        .clk(clk),
        .dataIn(rfReadData1),
        .dataOut(adrDataOut)
    );

    DataRegister bdr(
        .clk(clk),
        .dataIn(rfReadData2),
        .dataOut(bdrDataOut)
    );

    DataRegister aluoutdr(
        .clk(clk),
        .dataIn(aluResult),
        .dataOut(aluoutdrDataOut)
    );

    DataRegister dbdr(
        .clk(clk),
        .dataIn(dbdrDataIn),
        .dataOut(dbdrDataOut)
    );

    ExtendUnit eu(
        .selector(ExtSel),
        .dataIn(instruction[15:0]),
        .dataOut(extendResult)
    );

    InstructionMemory im(
        .readWriteOp(InsMemRW),
        .address(pcAddressOut),
        .dataIn(imDataIn),
        .dataOut(imDataOut)
    );

    InstructionRegister ir(
        .clk(clk),
        .IRWre(IRWre),
        .dataIn(imDataOut),
        .dataOut(instruction)
    );

    ProgramCounter pc(
        .clk(clk),
        .reset(reset),
        .writeOp(PCWre),
        .addressIn(pcAddressIn),
        .addressOut(pcAddressOut)
    );

    RegisterFile rf(
        .clk(clk),
        .init(init),
        .writeOp(RegWre),
        .readReg1(instruction[25:21]),
        .readReg2(instruction[20:16]),
        .writeReg(rfWriteReg),
        .writeData(rfWriteData),
        .readData1(rfReadData1),
        .readData2(rfReadData2)
    );

    Selector2 aluSelectA(
        .selector(ALUSrcA),
        .dataIn0(adrDataOut),
        .dataIn1({ 27'B0, instruction[10:6] }),
        .dataOut(aluA)
    );

    Selector2 aluSelectB(
        .selector(ALUSrcB),
        .dataIn0(bdrDataOut),
        .dataIn1(extendResult),
        .dataOut(aluB)
    );

    Selector2 dbSelectDataOut(
        .selector(DBDataSrc),
        .dataIn0(aluResult),
        .dataIn1(dmDataOut),
        .dataOut(dbdrDataIn)
    );

    Selector2 rfSelectWriteData(
        .selector(WrRegDSrc),
        .dataIn0(pcAddressOutPlus4),
        .dataIn1(dbdrDataOut),
        .dataOut(rfWriteData)
    );

    Selector4 rfSelectWriteReg(
        .selector(RegDst),
        .dataIn0({ 27'B0, 5'B11111 }),
        .dataIn1({ 27'B0, instruction[20:16] }),
        .dataIn2({ 27'B0, instruction[15:11] }),
        .dataIn3(32'Bz),
        .dataOut({ tmp[31:5] , rfWriteReg })
    );

    Selector4 pcSelectAddress(
        .selector(PCSrc),
        .dataIn0(pcAddressOutPlus4),
        .dataIn1(pcAddressOutPlus4PlusOffset),
        .dataIn2(rfReadData1),
        .dataIn3({ pcAddressOutPlus4[31:28], instruction[25:0], 2'B0 }),
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
