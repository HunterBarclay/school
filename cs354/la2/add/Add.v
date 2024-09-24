/**
Adder Module:
Computes the addition of two values.

Author: Jeff, Buffenbarger, Hunter Barclay
Date: Sept. 24th, 2024
Course: CS 354

DISCLAIMER: This module is a slightly modified version of the Multiplier module. Most of this I didn't write.

PARAMETERS:
- BITS: Width of inputs and output. (Default = 32)
- CLKS: Number of clock cycles to wait before enabling the output. (Default = 0)

INPUT:
- CLK: Clock
- A: First parameter to add. (Width of BITS)
- B: Second parameter to add. (Width of BITS)
- IEA: Enable input A.
- IEB: Enable input B.

OUTPUTS:
- Y: Output that is the sum of A and B.
- OE: Output is ready for consumption.
*/
module Adder#(BITS=32, CLKS=3'd0)(
    input CLK,
    input [BITS-1:0]A, B,
    input IEA, IEB,
    output reg [BITS-1:0]Y,
    output reg OE);

    reg [BITS-1:0]a, b;

    reg [2:0]cnt;		// extra clocks for multiplication

    enum {StINIT,StA,StB,StAB,StOE} state;

    initial begin
        state<=StINIT;
    end

    always @ (posedge CLK) begin
        case (state)
            StINIT: begin
                cnt<=CLKS;
                OE<=0;
                if (IEA && !IEB) begin
                    a<=A; state<=StA;
                end
                if (!IEA && IEB) begin
                    b<=B; state<=StB;
                end
                if (IEA && IEB) begin
                    a<=A; b<=B; state<=StAB;
                end
            end
            StA: begin
                if (IEB) begin
                    b<=B; state<=StAB;
                end
            end
            StB: begin
                if (IEA) begin
                    a<=A; state<=StAB;
                end
            end
            StAB: begin
                Y<=a+b;
                if (cnt)
                    cnt<=(cnt-3'b1);
                else
                    state<=StOE;
            end
            StOE: begin
                OE<=1;
                if (OE && !IEA && !IEB)
                    state<=StINIT;
            end
        endcase
    end
      
endmodule
