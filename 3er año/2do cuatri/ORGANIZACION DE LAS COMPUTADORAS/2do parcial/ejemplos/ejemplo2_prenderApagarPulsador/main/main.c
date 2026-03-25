extern void leer_pulsador_y_controlar_led_asm(void);
void app_main(void)
{
 printf("Iniciando...\n");
 configurar_gpio_asm(); // Configura GPIO1 como salida
 printf("Esperando pulsador en GPIO3\n");
 leer_pulsador_y_controlar_led_asm(); // Bucle infinito en ASM
}
