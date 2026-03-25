module div(
    input wire clk,
    input wire rst,
    input wire start,
    input wire [3:0] numerador,
    input wire [3:0] denominador,
    output wire [3:0] cociente,
    output wire [3:0] resto,
    output wire finish
);
//-----------------------------------------------------------
localparam[1:0]
    carga = 2'b00,       //carga de los valores
    validacion = 2'b01,  //validamos que num>dem
    calculo = 2'b10,     //realizamos el calculo
    finalizado = 2'b11;  //seteamos la maquina en 0
//------------------------------------------------------------
reg[1:0] state_reg,state_next;                                    //variables internas y no se asignan con <= sino con = 
reg[3:0] numerador_reg, denominador_reg , cociente_reg,  resto_reg;
reg[3:0] numerador_next,denominador_next, cociente_next,resto_next;
reg finish_reg,finish_next;
//------------------------------------------------------------
always @(posedge clk, posedge rst) begin
    if (rst) begin
        state_reg <= 2'b00;
        numerador_reg <= 4'b0000;
        denominador_reg <= 4'b0000;
        cociente_reg <= 4'b0000;
        resto_reg <= 4'b0000;
        finish_reg <= 1'b0;
    end else begin
        state_reg <= state_next;
        numerador_reg <= numerador_next;
        denominador_reg <= denominador_next;
        cociente_reg <= cociente_next;
        resto_reg <= resto_next;
        finish_reg <= finish_next;
    end
end
//------------------------------------------------------------
always @*
begin
    state_next=state_reg;
    finish_next = 1'b0;
    numerador_next = numerador_reg;
    denominador_next = denominador_reg;    
    cociente_next = cociente_reg;
    resto_next = resto_reg;

     case(state_reg)
        carga:
            begin
                if(start)begin
                state_next = validacion;  
                numerador_next = numerador;
                denominador_next = denominador;
                cociente_next=4'b0000;
                resto_next = numerador;
                finish_next=1'b0;
            end
            end 
        validacion:
            begin
            if(denominador_reg == 4'b0000)begin     // si el numerador es > al denominador
                state_next = finalizado;                        //el proximo estado es el finalizado
                cociente_next=4'b1111 ;          
                resto_next = 4'b1111; 
                finish_next=finish_reg;
            end else if(numerador_reg<denominador_reg) begin    //si el numerador>eldenominador
                state_next = finalizado;                        //el proximo estado es el finalizado    
                finish_next=finish_reg;
            end else if (numerador_reg>=denominador_reg)begin 
                state_next = calculo;                   // el proximo estado es el calculo 
                finish_next=finish_reg;
            end
            end 
        
        calculo:
            begin
                state_next = validacion;               // el proximo estado es el finalizado 
                numerador_next = numerador_reg - denominador_reg;        //numerador_reg - denominador_reg;    //obtenemos el numerador siguiente: restamos num actual - den actual
                denominador_next = denominador_reg;    //el denominador siempre es el mismo
                cociente_next= cociente_reg + 1;       //el contador es cuanta veces entra el denominador en el numerador, por eso es un contador           
                resto_next = resto_reg - denominador_reg;  
                finish_next=1'b0;
            end

        finalizado:
            begin
                state_next = carga;
                finish_next = 1'b1;
            end
        
    endcase
end

assign cociente=cociente_reg;
assign resto=resto_reg;
assign finish=finish_reg;
endmodule


