`timescale 1ns / 1ps

module Button(
    input mclk,
    input in,
    output wire out
    );

    reg clk, q1, q2, q3;

    assign out = q2 | q3;

    reg [15:0] counter;
    parameter [15:0] MAX_COUNTER = 16'D5_0000;

    initial begin
        clk = 0;
        q1 = 0;
        q2 = 0;
        q3 = 0;
    end

    always@(posedge mclk) begin
        counter = counter + 1;
        if (counter == MAX_COUNTER) begin
            clk = ~clk;
            counter = 0;
        end
    end

    always@(posedge clk) begin
        q1 <= in;
        q2 <= in;
        q3 <= in;
    end
endmodule
