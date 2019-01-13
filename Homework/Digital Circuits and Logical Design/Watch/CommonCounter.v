`timescale 1ns / 1ps

module CommonCounter(
  input mclk,            // ʱ���ź�, ����������������CLK, 
                           // ���뱣֤��·���е�ʱ�����м�ʱ����Ҫ������ʱ���ź�
  input en,              // ʹ���ź�, ������������������������CLK
  input [7:0] s,         // ��ʼ״̬(�ɴ�)
  input [7:0] e,         // ��ֹ״̬(���ɴ�)
  input [7:0] init,      // ��ʼ������ֵ
  output reg [7:0] num,  // ��ǰ״̬���
  output reg tc          // ��λ���
  );
  
reg init_tmp;
reg [7:0] tmp;
  
initial begin
  init_tmp = 0;
  tc = 0;
end

// ���ź����ڽ��initial�޷���Basys3��ʼ������ֵ����, ���볤�ڴ���, ����Counter�Ƿ���
always@(posedge mclk) begin
  if(init_tmp) num = tmp;
  else num = init;
end

// ��ʱ��, clk
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