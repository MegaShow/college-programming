`timescale 1ns / 1ps

module TimeCounter(
  input clk,                    // Basys3的100MHz脉冲
  input clk_5000_0000,
  input clk_500_0000,
  input clk_50_0000,
  input clk_5_0000,
  input clk_5000,
  input clk_500,
  input clk_50,
  input clk_5,
  input btn_show,               // Button Right, 切换显示的内容
  input btn_set,                //
  input btn_add,                // 
  output reg [3:0] show_state,  // 链接4个LED灯, 提示目前显示内容
  output reg set_led,
  output reg add_led,
  output wire [7:0] display,    // 段选端
  output wire [3:0] an          // 位选段
  );

reg base_clk;
reg [15:0] num;
// 值
wire [7:0] sec, min, hour, day, month, year;
// 进位
wire tc_sec_to_min, tc_min_to_hour, tc_hour_to_day,
     tc_day_to_month, tc_month_to_year, nil;

reg [1:0] show_signal;  // 2'B00 => min, sec
                        // 2'B01 => hour, min
                        // 2'B10 => month, day
                        // 2'B11 => year

reg [2:0] set_signal;  // 3'B000 => normal
                       // 3'B001 => sec
                       // 3'B010 => min
                       // 3'B011 => hour
                       // 3'B100 => day
                       // 3'B101 => month
                       // 3'B110 => year
                       // 3'B111 => return normal

reg [5:0] set_state; // {year, month, day, hour, min, sec}
reg [5:0] add_state; // {year, month, day, hour, min, sec}

reg btn_show_state, btn_set_state, btn_add_state;

reg [31:0] counter;
reg [3:0] flash;

reg [31:0] MAX_COUNTER = 32'D5000_0000;

CommonCounter sec_cc(
  .mclk(clk),
  .en((base_clk & ~set_led) | add_state[0]),
  .s(8'H00),
  .e(8'H60),
  .init(8'H00),
  .num(sec),
  .tc(tc_sec_to_min)
);

CommonCounter min_cc(
  .mclk(clk),
  .en((tc_sec_to_min & ~set_led) | add_state[1]),
  .s(8'H00),
  .e(8'H60),
  .init(8'H20),
  .num(min),
  .tc(tc_min_to_hour)
);

CommonCounter hour_cc(
  .mclk(clk),
  .en((tc_min_to_hour & ~set_led) | add_state[2]),
  .s(8'H00),
  .e(8'H24),
  .init(8'H14),
  .num(hour),
  .tc(tc_hour_to_day)
);

CommonCounter day_cc(
  .mclk(clk),
  .en((tc_hour_to_day & ~set_led) | add_state[3]),
  .s(8'H01),
  .e(8'H31),
  .init(8'H19),
  .num(day),
  .tc(tc_day_to_month)
);

CommonCounter month_cc(
  .mclk(clk),
  .en((tc_day_to_month & ~set_led) | add_state[4]),
  .s(8'H01),
  .e(8'H13),
  .init(8'H12),
  .num(month),
  .tc(tc_month_to_year)
);

CommonCounter year_cc(
  .mclk(clk),
  .en((tc_month_to_year & ~set_led) | add_state[5]),
  .s(8'H00),
  .e(8'Ha0),
  .init(8'H17),
  .num(year),
  .tc(nil)
);

Print print(.clk(clk), .num(num), .flash(flash), .display(display), .an(an));

initial begin
  base_clk = 0;
  counter = 0;
  flash = 0;
  show_signal = 0;
  set_signal = 0;
  btn_show_state = 0;
  btn_set_state = 0;
  btn_add_state = 0;
  set_led = 0;
  add_led = 0;
  MAX_COUNTER = 32'D5000_0000;
end

always@(posedge clk) begin
  // 模拟button的posedge状态, state储存的是前一个状态
  add_state = 0;
  if(btn_show != btn_show_state && !btn_show_state) begin
    show_signal = show_signal + 1;
  end
  if(btn_set != btn_set_state && !btn_set_state) begin
    set_signal = set_signal + 1;
  end
  if(btn_add != btn_add_state && !btn_add_state) begin
    if(set_signal != 0) begin
      case(set_signal)
        3'B001: add_state[0] = 1;  // sec
        3'B010: add_state[1] = 1;  // min
        3'B011: add_state[2] = 1;  // hour
        3'B100: add_state[3] = 1;  // day
        3'B101: add_state[4] = 1;  // month
        3'B110: add_state[5] = 1;  // year
      endcase
    end
  end
  btn_show_state = btn_show;
  btn_set_state = btn_set;
  btn_add_state = btn_add;
  counter = counter + 1;
  if(counter >= MAX_COUNTER) begin
    counter = 0;
    base_clk = ~base_clk;
  end
  case(show_signal)
    2'B00: begin num = {min, sec};    show_state = 4'B0001; end
    2'B01: begin num = {hour, min};   show_state = 4'B0010; end
    2'B10: begin num = {month, day};  show_state = 4'B0100; end
    2'B11: begin num = {8'H20, year}; show_state = 4'B1000; end
  endcase
  case(set_signal)
    3'B000: begin set_state = 6'B000000; flash = 4'B0000; end
    3'B001: begin set_state = 6'B000001; flash = 4'B0011; show_signal = 2'B00; end
    3'B010: begin set_state = 6'B000010; flash = 4'B1100; show_signal = 2'B00; end
    3'B011: begin set_state = 6'B000100; flash = 4'B1100; show_signal = 2'B01; end
    3'B100: begin set_state = 6'B001000; flash = 4'B0011; show_signal = 2'B10; end
    3'B101: begin set_state = 6'B010000; flash = 4'B1100; show_signal = 2'B10; end
    3'B110: begin set_state = 6'B100000; flash = 4'B1111; show_signal = 2'B11; end
    3'B111: begin set_state = 6'B000000; flash = 4'B0000; show_signal = 2'B00; set_signal = 3'B000; end
  endcase
  if(set_state == 0) set_led = 0;
  else set_led = 1;
  if(add_state == 0) add_led = 0;
  else add_led = 1;
end

always@(clk_5000_0000, clk_500_0000, clk_50_0000, clk_5_0000,
        clk_5000, clk_500, clk_50, clk_5) begin
  if(clk_5000_0000) MAX_COUNTER = 5000_0000;
  else if(clk_500_0000) MAX_COUNTER = 500_0000;
  else if(clk_50_0000) MAX_COUNTER = 50_0000;
  else if(clk_5_0000) MAX_COUNTER = 5_0000;
  else if(clk_5000) MAX_COUNTER = 5000;
  else if(clk_500) MAX_COUNTER = 500;
  else if(clk_50) MAX_COUNTER = 50;
  else if(clk_5) MAX_COUNTER = 5;
  else MAX_COUNTER = 5000_0000;
end

endmodule