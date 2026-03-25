module TFI(
    input wire CLK,
    input BTN1,//BotonA
    input BTN2, //BotonB
    output wire LED3,
    output wire LED2,
    output wire LED1,
    output wire LED0
);

wire botonA_estable, botonB_estable;
wire entrada, salida;
wire [3:0] espacio;




sensores sensores_instacia(
    .clk(CLK),
    .botonA(BTN1),
    .botonB(BTN2),
    .botonA_estable(botonA_estable),
    .botonB_estable(botonB_estable)
);

detector detector_instancia(
    .clk(CLK),
    .botonA(botonA_estable),
    .botonB(botonB_estable),
    .entrada(entrada),
    .salida(salida)
);

contar_autos contador_instancia(
    .clk(CLK),
    .entrada(entrada),
    .salida(salida),
    .espacio(espacio)
);
assign {LED3,LED2,LED1,LED0}={1'b0,espacio}; 
endmodule