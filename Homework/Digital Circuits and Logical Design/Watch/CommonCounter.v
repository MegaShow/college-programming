`timescale 1ns / 1ps

module CommonCounter(
  input mclk,            // 时钟信号, 不是驱动计数器的CLK, 
                           // 必须保证电路运行的时候所有计时器都要触发该时钟信号
  input en,              // 使能信号, 或许是真正的驱动计数器的CLK
  input [7:0] s,         // 初始状态(可达)
  input [7:0] e,         // 终止状态(不可达)
  input [7:0] init,      // 初始化置数值
  output reg [7:0] num,  // 当前状态输出
  output reg tc          // 进位输出
  );
  
reg init_tmp;
reg [7:0] tmp;
  
initial begin
  init_tmp = 0;
  tc = 0;
end

// 该信号用于解决initial无法在Basys3初始化置数值问题, 必须长期触发, 无论Counter是否工作
always@(posedge mclk) begin
  if(init_tmp) num = tmp;
  else num = init;
end

// 真时钟, clk
always@(posedge en) begin
  if(init_tmp == 0) begin
    init_tmp = 1;
    tmp = init;
  end
  tc = 0;
  tmp[3:0] = tmp[3:0] + 1;
  if(tmp[3:0] == 4'D10) begin
    tmp[3:0] = 0;
    tmp[7:4] = tmp[7:4] + 1;
  end
  if(tmp == e) begin
    tc = 1;
    tmp = s;
  end
end

endmodule