`timescale 1ns/100ps

module fib#(BITS=16)();

    reg clk;
    reg [BITS]inp; // data read: ARD -> EPT
    reg [BITS]out; // data writ: EPT -> ARD
    reg ie, oe;    // input/output enable

    Fibonacci#(.BITS(BITS)) f(
        .CLK(clk),
        .INP(inp),
        .IE(ie),
        .OUT(out),
        .OE(oe)
    );

    always #7.5 clk=~clk; // create a 66Mhz clock (15ns period)

    integer i;
    initial begin
        clk=1'b0;			// enabled
        // 0 1 2 3 4 5 6  7  8  9 10 11  12  13  14  15  16
        // 0 1 1 2 3 5 8 13 21 34 55 89 144 233 377 610 987
        for (i=0; i<=16; i++) begin
	        ie=1;
	        inp=i;			// provide input
	        #30;
	        ie=0;			// input latched during ie
	        wait (oe);		// until output good
	        $display("fact(%1d)=%1d",inp,out);
        end
    $stop;
    end

// `include "monitor"

endmodule
