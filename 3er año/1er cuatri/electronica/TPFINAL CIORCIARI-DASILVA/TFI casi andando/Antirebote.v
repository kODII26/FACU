module antirrebote(
    input wire clk,
    input wire senal_entrada,  
    output reg salida_limpia   
);
    reg [19:0] contador;      
    reg salida_reg;

    initial begin
        salida_limpia = 0;
        contador = 0;
        salida_reg = 0;
    end

    always @(posedge clk) begin
        if (senal_entrada != salida_reg) begin
            contador <= 20'b0; // Reiniciamos el contador si hay un cambio en la señal
            salida_reg <= senal_entrada; // Actualizamos el registro de la señal
        end else if (contador < 20'd100000) begin // Ajustamos el tiempo de estabilización
            contador <= contador + 1; // Incrementamos el contador
        end else begin
            salida_limpia <= salida_reg; // Actualizamos la salida limpia solo si el contador llega al límite
        end
    end
endmodule