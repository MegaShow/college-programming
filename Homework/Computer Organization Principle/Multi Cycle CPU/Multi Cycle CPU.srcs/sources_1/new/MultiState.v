`timescale 1ns / 1ps

module MultiState(
    input clk,
    input rst,
    input [5:0] op,

    output [2:0] state
    );

    reg [2:0] tmp;

    assign state = tmp;

    always@(posedge clk) begin
        if (rst == 0) begin
            tmp = 3'B000;
        end else begin
            case (tmp)
                3'B000: tmp = 3'B001;
                3'B001: begin
                    if (op[5:3] == 3'B111) begin // j, jal, jr, halt
                        tmp = 3'B000;
                    end else begin // others
                        tmp = 3'B010;
                    end
                end
                3'B010: begin
                    if (op[5:2] == 4'B1101) begin // beq, bltz
                        tmp = 3'B000;
                    end else if (op[5:2] == 4'B1100) begin // sw, lw
                        tmp = 3'B100;
                    end else begin // others
                        tmp = 3'B011;
                    end
                end
                3'B011: tmp = 3'B000;
                3'B100: begin
                    if (op[0] == 1) begin // lw
                        tmp = 3'B011;
                    end else begin
                        tmp = 3'B000;
                    end
                end
            endcase
        end
    end

endmodule
