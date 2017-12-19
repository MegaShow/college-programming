`timescale 1ns / 1ps

module PCMain(CLK, D, Q, display, AN, DP, BI_RBO);
  input CLK, D;
  output [3:0] Q;
  output reg DP;
  output reg [3:0] AN;
  output [7:0] display;
  inout BI_RBO;
  reg [31:0] counter;
  reg [31:0] dis_counter;
  reg PC_CLK;
  reg POWER;
  reg DIS_CLK;
  pc t(.CLK(PC_CLK), .D(D), .POWER(POWER), .Q3(Q[3]), .Q2(Q[2]), .Q1(Q[1]), .Q0(Q[0]),
    .CA(display[7]), .CB(display[6]), .CC(display[5]), .CD(display[4]),
    .CE(display[3]), .CF(display[2]), .CG(display[1]),
    .DIS_CLK(DIS_CLK), .BI_RBO(BI_RBO));
  
  initial begin
    DP = 1;
    AN = 4'B1101;
    POWER = 1;
    PC_CLK = 0;
    DIS_CLK = 0;
    counter = 0;
    dis_counter = 0;
  end
  
  always@(posedge CLK) begin
    counter = counter + 1;
    if (counter == 5000_0000) begin
      counter = 0;
      PC_CLK = ~PC_CLK;
    end
    dis_counter = dis_counter + 1;
    if (dis_counter == 5_0000) begin
      dis_counter = 0;
      DIS_CLK = ~DIS_CLK;
      case(DIS_CLK)
        1'B0: AN = 4'B1101;
        1'B1: AN = 4'B1110;
      endcase
    end
  end
endmodule
