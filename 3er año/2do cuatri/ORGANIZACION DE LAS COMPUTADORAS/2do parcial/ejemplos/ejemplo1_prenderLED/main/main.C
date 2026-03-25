#include <stdio.h> // Para printf
#include <freertos/FreeRTOS.h> // Para vTaskDelay y pdMS_TO_TICKS
#include <freertos/task.h> // Para vTaskDelay

extern void configurar_gpio_asm(void);
extern void encender_led_asm(void);
extern void apagar_led_asm(void);
void app_main(void)
{
 printf("Probando LED RGB en GPIO1\n");
 configurar_gpio_asm();

 while(1) {
 printf("GPIO1 = HIGH\n");
 encender_led_asm(); // GPIO1 = 1
 vTaskDelay(pdMS_TO_TICKS(2000));

 printf("GPIO1 = LOW\n");
 apagar_led_asm(); // GPIO1 = 0
 vTaskDelay(pdMS_TO_TICKS(2000));
 }
}