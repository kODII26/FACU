module visualizacion(
    input wire [6:0] espacio,
    output wire [3:0] leds
);

assign leds= espacio[3:0];

endmodule
