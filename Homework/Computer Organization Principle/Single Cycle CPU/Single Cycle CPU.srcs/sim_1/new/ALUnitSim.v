`timescale 1ns / 1ps

module ALUnitSim();
    reg [31:0] a;
    reg [31:0] b;
    reg [2:0] op;

    wire [31:0] result;
    wire zero;

    ALUnit alu(
        .a(a),
        .b(b),
        .op(op),
        .result(result),
        .zero(zero)
    );

    initial begin
        a = 0;
        b = 0;
        op = 0;

        // a + b
        #100
        a = 11;
        b = 1;
        op = 3'B000;

        // a - b
        #100
        a = 11;
        b = 1;
        op = 3'B001;

        // b << a
        #100
        a = -6;
        b = -1234;
        op = 3'B010;

        // a | b
        #100
        a = 1234;
        b = 1111;
        op = 3'B011;

        // a & b
        #100
        a = 1234;
        b = 1111;
        op = 3'B100;

        // a < b unsigned
        #100
        a = -12;
        b = 11;
        op = 3'B101;

        // a < b signed
        #100
        a = -12;
        b = -11;
        op = 3'B110;

        // a ^ b
        #100
        a = 1234;
        b = 1111;
        op = 3'B111;
    end
endmodule
