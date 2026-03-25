module mux_4_1 (
    input wire[3:0] conta_num,conta_den,cociente,resto,
    input wire[1:0] Sel,
    output reg[3:0] LEDS
);
always @* begin
    case(Sel)
        2'b00 : begin
            LEDS<=conta_num;
        end
        2'b01 : begin
            LEDS<=conta_den;
        end
        2'b10 : begin
            LEDS <= cociente;
        end
        2'b11 : begin
            LEDS<=resto;
        end
        default : begin
            LEDS <= conta_num;
        end

    endcase

end
endmodule