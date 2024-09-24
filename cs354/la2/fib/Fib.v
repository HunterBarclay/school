/**
Fibonacci Module:
The Fibonacci module takes in an index and returns that value in
the Fibonacci sequence at that index.

Author: Hunter Barclay
Date: Sept. 24th, 2024
Course: CS 354

The Fibonacci sequence (FX) is defined as follows, with X being
the index in the sequence:

F0 = 0
F1 = 1
FN = F(N-1) + F(N-2)

where N is any natural number.

PARAMETERS:
- BITS  -> Number of bits to use for INP and OUT. (Default = 32)

INPUTS:
- INP   -> Target index of the Fibonacci sequence. (Width = BITS)
- IE    -> Tells the module that the input is available and begins a new calculation.

OUTPUTS:
- OUT   -> The value at the INPth index of the Fibonacci sequence. (Width = BITS)
- OE    -> Signals that OUT is ready for consumption.

USAGE WARNING:
At the moment, if you set IE to one for a single clock cycle while in the middle of computation,
while it is finishing the latest calculation, it will fail to reset the module, and will begin
calculating the new INP(plus the current internal index)th element in the sequence.
 */
module Fibonacci#(BITS=32)(
    input CLK,
    input      [BITS-1:0]INP, input      IE,
    output reg [BITS-1:0]OUT, output reg OE);

    wire [BITS-1:0]add_out, sto1_out;
    wire ctr_init, ctr_oe, sto1_oe, sto2_oe, add_oe;

    localparam false=1'b0;
    localparam true=1'b1;
    localparam zero=BITS'(0);
    localparam one=BITS'(1);

    // The counter will keep track of the indexes we already have calculated and know when to stop.
    // Otherwise, the output is unused.
    Counter#(.BITS(BITS)) ctr(
        .CLK(CLK),
        .INP(INP),
        .IE(IE),
        .OUT(),         // unused
        .OE(ctr_oe),
        .DECR(true),    // count down
        .STOP(zero),    // for (OUT=INP; OUT>1; OUT--)
        .CE(add_oe),
        .INIT(ctr_init),
        .DONE(OE)
    );

    // The adder will add up the values we have saved in our storage modules.
    Adder#(.BITS(BITS)) add(
        .CLK(CLK),
        .A(OUT),
        .IEA(sto2_oe),
        .B(sto1_out),
        .IEB(sto1_oe),
        .Y(add_out),
        .OE(add_oe)
    );

    Store#(.BITS(BITS), .FIRST(one)) sto1(
        .CLK(CLK),
        .INP(add_out),
        .IE(ctr_oe),
        .OUT(sto1_out),
        .OE(sto1_oe),
        .INIT(ctr_init)
    );

    Store#(.BITS(BITS), .FIRST(zero)) sto2(
        .CLK(CLK),
        .INP(sto1_out),
        .IE(ctr_oe),
        .OUT(OUT),
        .OE(sto2_oe),
        .INIT(ctr_init)
    );

endmodule
