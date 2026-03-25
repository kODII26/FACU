`timescale 1ns / 1ps

module TFI_tb;

    // Entradas
    reg clk;
    reg botonA;
    reg botonB;

    // Salidas
    wire [3:0] leds;

    // Instancia del módulo TFI
    TFI uut (
        .CLK(clk),       // Conecta el reloj
        .BTN1(botonA),   // Conecta el botón A
        .BTN2(botonB),   // Conecta el botón B
        .LED3(leds[3]),  // Conecta el LED3
        .LED2(leds[2]),  // Conecta el LED2
        .LED1(leds[1]),  // Conecta el LED1
        .LED0(leds[0])   // Conecta el LED0
    );

    // Generador de reloj
    always #10 clk = ~clk; // Reloj de 50 MHz (20 ns por ciclo)

    initial begin
        // Inicialización del archivo .vcd
        $dumpfile("TFI_tb.vcd"); // Nombre del archivo .vcd
        $dumpvars(0, uut); // Registra solo las señales del módulo principal TFI

        // Inicialización
        clk = 0;
        botonA = 0;
        botonB = 0;

        // Simulamos el patrón de ingreso de un auto
        #200 botonA = 1;  // Presionamos botonA (20 us)
        #20000 botonB = 1;  // Presionamos botonB (20 us)
        #200 botonA = 0;  // Soltamos botonA (20 us)
        #20000 botonB = 0;  // Soltamos botonB (20 us)

        // Esperamos para observar el resultado
        #100000;

        // Simulamos el patrón de egreso de un auto
        #20000 botonB = 1;  // Presionamos botonB (20 us)
        #20000 botonA = 1;  // Presionamos botonA (20 us)
        #20000 botonB = 0;  // Soltamos botonB (20 us)
        #20000 botonA = 0;  // Soltamos botonA (20 us)

        // Esperamos para observar el resultado
        #100000;

        // Finalizamos la simulación
        $finish; // Finaliza la simulación correctamente
    end
endmodule