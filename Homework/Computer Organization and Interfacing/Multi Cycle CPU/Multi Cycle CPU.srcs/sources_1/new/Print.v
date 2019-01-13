`timescale 1ns / 1ps

module Print(
    input mclk,
    input [15:0] num,
    output reg [7:0] display,
    output reg [3:0] an
    );

    reg [3:0] tmp;
    reg [15:0] counter;

    parameter [15:0] MAX_COUNTER = 16'D5_0000;

    initial begin
        an = 4'B0111;
        counter = 0;
    end

    always@(posedge mclk) begin
        counter = counter + 1;
        if (counter == MAX_COUNTER) begin
            an = (an >> 1) + 4'B1000;
            if (an == 4'B1111) begin
                an = 4'B0111;
            end
            counter = 0;
            case(an)
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
                4'Ha: display = 8'B0001_0001;
                4'Hb: display = 8'B1100_0001;
                4'Hc: display = 8'B0110_0011;
                4'Hd: display = 8'B1000_0101;
                4'He: display = 8'B0110_0001;
                4'Hf: display = 8'B0111_0001;
            endcase
        end
    end
endmodule
