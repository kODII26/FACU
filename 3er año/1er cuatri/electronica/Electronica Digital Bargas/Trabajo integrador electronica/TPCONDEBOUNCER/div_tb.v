`default_nettype none
`define DUMPSTR(x) `"x.vcd`"
`timescale 100 ns / 100 ns

module div_tb();

parameter DURATION = 1000;
reg clk = 0;
always #0.5 clk = ~clk;

reg test_start;
reg test_rst;
reg [3:0] test_numerador;
reg [3:0] test_denominador;
wire [3:0] test_cociente;
wire [3:0] test_resto;
wire test_finish;



div UUT (
    .clk(clk),
    .start(test_start),
    .rst(test_rst),
    .numerador(test_numerador),
    .denominador(test_denominador),
    .cociente(test_cociente),
    .resto(test_resto),
    .finish(test_finish)
);

initial begin
    $dumpfile(`DUMPSTR(`VCD_OUTPUT));
    $dumpvars(0, div_tb);

    test_rst = 1'b0;
    test_start = 1'b0;
    test_numerador = 4'b0000;
    test_denominador = 4'b0000;

    #1
    test_rst = 1'b1;
    #1
    test_rst = 1'b0;
    
    #10 
    test_numerador = 4'b1000;
    test_denominador = 4'b0010;
    test_start = 1'b1;

    #30 
    test_start = 1'b0;
  
    #30
    test_rst = 1'b1;
    #30
    test_rst = 1'b0;

    #30
    test_numerador = 4'b1000;
    test_denominador = 4'b0000;
    test_start = 1'b1;



    


    #(DURATION) $display("End of simulation");
    $finish;
end


endmodule