
module top(
input wire clk,
input wire rst,
input wire [3:0] xBTN,
output wire [3:0] LED
);

//-----------------------------------------------------------------------------------------
//INVERSOR DE BOTONES PARA LA FPGA
wire [3:0] BTN;
wire [3:0] BTND ;
wire [3:0] BTNE;
wire GND = 0;
db_fsm debouncing3(
    .clk(clk),
    .reset(GND),
    .sw(xBTN[3]),
    .db(BTND[3])
);
db_fsm debouncing2(
    .clk(clk),
    .reset(GND),
    .sw(xBTN[2]),
    .db(BTND[2])
);
db_fsm debouncing1(
    .clk(clk),
    .reset(GND),
    .sw(xBTN[1]),
    .db(BTND[1])
);
db_fsm debouncing0(
    .clk(clk),
    .reset(GND),
    .sw(xBTN[0]),
    .db(BTND[0])
);
assign BTN[0] = ~xBTN[0];       ///INVERSION
assign BTN[1] = ~xBTN[1];        ///INVERSION
assign BTN[2] = ~xBTN[2];       ///INVERSION
assign BTN[3] = ~xBTN[3];       ///INVERSION

edge_detect_gate ed3(
    .clk(clk),
    .reset(GND),
    .level(BTN[3]),
    .tick(BTNE[3])
);
edge_detect_gate ed2(
    .clk(clk),
    .reset(GND),
    .level(BTN[2]),
    .tick(BTNE[2])
);
edge_detect_gate ed1(
    .clk(clk),
    .reset(GND),
    .level(BTN[1]),
    .tick(BTNE[1])
);
edge_detect_gate ed0(
    .clk(clk),
    .reset(GND),
    .level(BTN[0]),
    .tick(BTNE[0])
);


//-----------------------------------------------------------------------------------------
//ESTADOS Y REGISTROS
localparam [2:0]
cargar_num  = 3'b000,
cargar_den  = 3'b001,
chequeo     = 3'b010,
mostrar_coc = 3'b011,
mostrar_res = 3'b100;


//-----------------------------------------------------------------------------------------


wire [3:0] count_exi_num; 

contu cont_module_numerador (
    .clk(clk),
    .reset(BTNE[3]),
    .up(BTNE[1]),
    .down(BTNE[2]),
    .count(count_exi_num)
);

wire [3:0] count_exi_deno; 

contd cont_module_denominador (
    .clk(clk),
    .reset(BTNE[3]),
    .up(BTNE[1]),
    .down(BTNE[2]),
    .count(count_exi_deno)
);

//-----------------------------------------------------------------------------------------
wire [3:0] cociente,resto;
wire start,finish;

div div_module(
    .clk(clk),
    .rst(BTNE[3]),
    .start(start),
    .cociente(cociente),
    .numerador(count_exi_num),
    .resto(resto),
    .denominador(count_exi_deno),
    .finish(finish)
);
//-----------------------------------------------------------------------------------------
//MULTIPLEXOR PARA LAS SALIDA DE LOS LEDS

wire [1:0] sel;

mux_4_1 multiplexor_leds(
    .conta_num(count_exi_num),
    .conta_den(count_exi_deno),
    .cociente(cociente),
    .resto(resto),
    .Sel(sel),
    .LEDS(LED)
);
//-----------------------------------------------------------------------------------------
reg [1:0] sel_reg,sel_next;
reg start_reg,start_next;
reg [2:0] state_next,state_reg;

//-----------------------------------------------------------------------------------------
    always @(posedge clk, posedge BTNE[3]) begin
        if(BTNE[3])begin
            state_reg <= cargar_num;
            start_reg <= 1'b0;
            sel_reg <= 2'b00;
        end else begin
           state_reg <= state_next;
           sel_reg <= sel_next;
           start_reg <= start_next; 

        end
end

always @* begin
     state_next = state_reg;
     sel_next = sel_reg;       
     start_next = start_reg;    
              case(state_reg)   
                cargar_num: 
                begin
                    start_next = 1'b0;
                    sel_next = 2'b00;
                    if(BTNE[0]) begin    
                        state_next=cargar_den;
                    end

                end

                cargar_den: 
                begin
                    sel_next = 2'b01;
                      if(BTNE[0]) begin   
                    state_next=chequeo;
        
                      end
                end
                
                chequeo: 
                begin
                     start_next = 1'b1;
                     if(finish) state_next=mostrar_coc;
                 end

                mostrar_coc: 
                begin 
                    start_next = 1'b0;
                     sel_next = 2'b10;
                      if(BTNE[0]) begin   
                         state_next=mostrar_res;
                      end
                end


                mostrar_res: 
                begin
                    sel_next = 2'b11;
                    if(BTNE[0]) begin   
                    state_next=cargar_num;
                     end
                end
             endcase
    end

   assign sel = sel_reg;
   assign start = start_reg;
endmodule




