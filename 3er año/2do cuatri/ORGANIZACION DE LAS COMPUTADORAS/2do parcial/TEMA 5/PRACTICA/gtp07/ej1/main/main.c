#include <stdio.h>

// Estas funciones están definidas en tu archivo .S
extern void main(void);        // configura GPIO2–GPIO5 y GPIO6
extern void main_loop(void);   // bucle infinito: lee botón y muestra 1010

void app_main(void)
{
    printf("Iniciando ejemplo GPIO mano cerrada...\n");

    // 1) Configurar GPIO en ASM
    main();           // llama a la función ASM 'main' (la tuya), que hace la config

    printf("Configuración hecha. Entrando al bucle principal...\n");

    // 2) Entrar al loop ASM (no vuelve más)
    main_loop();

    // Nunca vamos a llegar acá porque main_loop es un bucle infinito,
    // pero lo dejamos por prolijidad.
    printf("main_loop terminó (esto no debería imprimirse).\n");
}