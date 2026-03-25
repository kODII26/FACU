//CONTADOR
module contar_autos(
    input wire clk,
    input wire entrada,
    input wire salida,
    output reg [3:0] espacio
);

initial begin
    espacio = 0;
end

always @(posedge clk) begin
    if (entrada && !salida && espacio < 7)
        espacio <= espacio + 1;
    else if (salida && !entrada && espacio > 0)
        espacio <= espacio - 1;
end
endmodule
