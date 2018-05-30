`timescale 1ns / 1ps

module Basys3Sim();
    reg [1:0] switch;
    reg mclk;
    reg btnClk;
    reg reset;
    wire [7:0] display;
    wire [3:0] an;

    Basys3 basys3(
        .switch(switch),
        .mclk(mclk),
        .btnClk(btnClk),
        .reset(reset),
        .display(display),
        .an(an)
    );

    initial begin
        mclk = 0;
        reset = 0;
        #15
        reset = 1;

        btnClk = 0;
        btnClk = 1;
        #1
        btnClk = 0;
    end

    always begin
        #1
        mclk = ~mclk;
        btnClk = ~btnClk;
    end
endmodule
