`timescale 1ns / 1ps

module Print(
  input clk,                 // ʱ���ź�
  input [15:0] num,          // Ҫ��ʾ��4λ��
  input [3:0] flash,         // 4λ, �Ƿ���˸, 1 => true, 0 => false
  output reg [7:0] display,  // ���, 8λ��ѡ��(CA, CB, CC, CD, CE, CF, CG, DP)
  output reg [3:0] an        // ���, 4λλѡ��
  );
  
reg flash_state;  // ��ǰ��˸״̬, 1 => ������˸״̬
reg [3:0] tmp;
reg [15:0] counter;
reg [31:0] flash_counter;
reg [3:0] an_tmp;
  
parameter [15:0] MAX_COUNTER = 16'D5_0000;
parameter [31:0] MAX_FLASH_COUNTER = 32'D5000_0000;
  
initial begin
  an_tmp = 4'B0111;
  counter = 0;
  flash_counter = 0;
  flash_state = 0;
end

always@(an_tmp) begin
  case(an_tmp)
    4'B0111: tmp = num[15:12];
    4'B1011: tmp = num[11:8];
    4'B1101: tmp = num[7:4];
    4'B1110: tmp = num[3:0];
  endcase
  case(tmp)
    4'H0: display = 8'B0000_0011;
    4'H1: display = 8'B1001_1111;
    4'H2: display = 8'B0010_0101;
    4'H3: display = 8'B0000_1101;
    4'H4: display = 8'B1001_1001;
    4'H5: display = 8'B0100_1001;
    4'H6: display = 8'B0100_0001;
    4'H7: display = 8'B0001_1111;
    4'H8: display = 8'B0000_0001;
    4'H9: display = 8'B0000_1001;
  endcase
end

always@(posedge clk) begin
  // ��ʾɨ��
  counter = counter + 1;
  if(counter == MAX_COUNTER) begin
    an_tmp = (an_tmp >> 1) + 4'B1000;
    counter = 0;
  end
  if(an_tmp == 4'B1111) begin
    an_tmp = 4'B0111;
  end
  // ��˸ɨ��
  flash_counter = flash_counter + 1;
  if(flash_counter == MAX_FLASH_COUNTER) begin
    flash_counter = 0;
    flash_state = ~flash_state;
  end
  // �������anֵ
  if(flash_state) an = an_tmp | flash;
  else an = an_tmp;
end

endmodule