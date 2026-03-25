module sensores(
    input wire clk,
    input botonA,
    input botonB,
    output wire botonA_estable,
    output wire botonB_estable
);

antirrebote antirreboteA(
    .clk(clk),
    .senal_entrada(botonA),
    .salida_limpia(botonA_estable)
);

antirrebote antirreboteB(
    .clk(clk),
    .senal_entrada(botonB),
    .salida_limpia(botonB_estable)
);

endmodule