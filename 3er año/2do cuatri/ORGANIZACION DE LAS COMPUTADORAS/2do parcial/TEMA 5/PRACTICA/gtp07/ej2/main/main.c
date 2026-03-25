#include <stdio.h>

// Estas funciones están definidas en tu archivo .S
extern void gpio_irq_init(void);        // configura 


void app_main(void)
{
    printf("Inicializando interrupción GPIO...\n");

    // 1. Configurar GPIO4 (LED) y GPIO5 (botón)
    //    + habilitar interrupción en canal 10
    //    + configurar tipo flanco
    gpio_irq_init();

    printf("Listo. Esperando interrupciones...\n");

    // 2. Bucle infinito como pide la consigna
    while (1) {
        // El programa NO hace nada aquí.
        // Todo el manejo está en la ISR (gpio_isr).
    }
}