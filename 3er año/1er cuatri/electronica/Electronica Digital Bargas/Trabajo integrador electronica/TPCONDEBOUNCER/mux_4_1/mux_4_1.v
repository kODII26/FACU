module mux_4_1 (
    input wire[3:0] conta_num,conta_den,cociente,resto,
    input wire[1:0] Sel,
    output reg LED0, LED1, LED2, LED3
);
always @* begin
    case(Sel)
        2'b00 : begin
            LED0 <= conta_num[0];
            LED1 <= conta_num[1];
            LED2 <= conta_num[2];
            LED3 <= conta_num[3];
        end
        2'b01 : begin
            LED0 <= conta_den[0];
            LED1 <= conta_den[1];
            LED2 <= conta_den[2];
            LED3 <= conta_den[3];
        end
        2'b10 : begin
            LED0 <= cociente[0];
            LED1 <= cociente[1];
            LED2 <= cociente[2];
            LED3 <= cociente[3];
        end
        2'b11 : begin
            LED0 <= resto[0];
            LED1 <= resto[1];
            LED2 <= resto[2];
            LED3 <= resto[3];
        end
        default : begin
            LED0 <= conta_num[0];
            LED1 <= conta_num[1];
            LED2 <= conta_num[2];
            LED3 <= conta_num[3];
        end

    endcase

end
endmodule