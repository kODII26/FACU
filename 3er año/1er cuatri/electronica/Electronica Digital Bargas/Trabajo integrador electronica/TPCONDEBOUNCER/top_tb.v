`default_nettype none
`define DUMPSTR(x) `"x.vcd`"
`timescale 100 ns / 100 ns

module top_tb();

//-- Simulation time: 1us (10 * 100ns)
parameter DURATION = 1000;

//-- Clock signal. It is not used in this simulation
reg clk = 0;
always #0.5 clk = ~clk;

//-- Leds port
reg [3:0] BUT; 
wire [3:0] LED;


//-- Instantiate the unit to test
top UUT (
           .clk(clk),
           .xBTN0(BUT[0]),
           .xBTN1(BUT[1]),
           .xBTN2(BUT[2]),
           .xBTN3(BUT[3]),
           .LED0(LED[0]),
           .LED1(LED[1]),
           .LED2(LED[2]),
           .LED3(LED[3])
         );

integer i;

initial begin
  $dumpfile(`DUMPSTR(`VCD_OUTPUT));
  $dumpvars(0, top_tb);

    BUT = 4'b0000;
   #10
    BUT[3] = 1'b1;
    #3
    BUT[3] = 1'b0;
/*
    #1
    rst = 1'b1;
    #1
    rst = 1'b0;

    // Cargo 2 en el numerador
    #10
    BUT[0] = 1'b1;
    #3
    BUT[0] = 1'b0;
    #10
    BUT[0] = 1'b1;
    #3
    BUT[0] = 1'b0;*/
    #10
    BUT[0] = 1'b1;
    #3
    BUT[0] = 1'b0;

    /*// Cargo 1 en el denominador 
    #10
    BUT[0] = 1'b1;
    #3
    BUT[0] = 1'b0;*/
    #10
    BUT[0] = 1'b1;
    #3
    BUT[0] = 1'b0;

  // Avanzo a ver el cociente
    #30
    BUT[0] = 1'b1;
    #3
    BUT[0] = 1'b0;

    // Avanzo a ver el resto
    #30
    BUT[0] = 1'b1;
    #3
    BUT[0] = 1'b0;

    // Avanzo para reiniciar
    #20
    BUT[0] = 1'b1;
    #3
    BUT[0] = 1'b0;



   #(DURATION) $display("End of simulation");
  $finish;
end

endmodule
