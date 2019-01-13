`timescale 1ns / 1ps
module Print(CLK, TYPE, DIS, AN, display);
  input CLK, TYPE, DIS;
  output reg [3:0] AN;  // 位选端(4位)
  output reg [7:0] display;  // 段选端(8位)
  reg [31:0] counter;  // 计数器, 用于适配显示间隔时间
  reg [31:0] move_counter;  // 计数器, 用于适配滚动间隔时间
  parameter [31:0] MAX_COUNTER = 5_0000;  // 显示间隔
  parameter [31:0] MAX_MOVE_COUNTER = 1_0000_0000;  // 滚动间隔
  parameter [31:0] ID = 32'H16340040;  // 学号
  reg [15:0] num;  // 需要显示的位数
  reg [4:0] tmp;  // 正在显示的数字
  
  initial begin
    AN = 4'B0111;
    display = 8'B0000_0000;
    counter = 0;
    move_counter = MAX_MOVE_COUNTER + 1;
    num = ID[15:0];
  end
  
  always@(AN) begin
    case(AN)
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
      4'Hf: display = 8'B1111_1111;  // blank
    endcase
  end
  
  always@(posedge CLK) begin
    counter = counter + 1;
    if(counter == MAX_COUNTER) begin
      AN = (AN >> 1) + 4'B1000;
      counter = 0;
    end
    if(AN == 4'B1111) begin
      AN = 4'B0111;
    end
    if(TYPE == 1) begin
      if(move_counter == MAX_MOVE_COUNTER + 1) begin
        // 如果move_counter == MAX_MOVE_COUNTER + 1
        // 则说明TYPE刚刚从0->1, 先复位num为前四位
        num = ID[31:16];
        move_counter = 0;
      end
      move_counter = move_counter + 1;
      if(move_counter == MAX_MOVE_COUNTER) begin
        // 滚动需要显示的学号
        case(num)
          ID[31:16]:            num = ID[27:12];
          ID[27:12]:            num = ID[23:8];
          ID[23:8]:             num = ID[19:4];
          ID[19:4]:             num = ID[15:0];
          ID[15:0]:             num = {ID[11:0], 4'Hf};
          {ID[11:0], 4'Hf}:     num = {ID[7:0], 8'Hff};
          {ID[7:0], 8'Hff}:     num = {ID[3:0], 12'Hfff};
          {ID[3:0], 12'Hfff}:   num = 16'Hffff;
          16'Hffff:             num = {12'Hfff, ID[31:28]};
          {12'Hfff, ID[31:28]}: num = {8'Hff, ID[31:24]};
          {8'Hff, ID[31:24]}:   num = {4'Hf, ID[31:20]};
          {4'Hf, ID[31:20]}:    num = ID[31:16];
        endcase
        move_counter = 0;
      end
    end else begin
      case(DIS)
        0: num = ID[15:0];
        1: num = ID[31:16];
      endcase
      move_counter = MAX_MOVE_COUNTER + 1;
    end
  end
endmodule