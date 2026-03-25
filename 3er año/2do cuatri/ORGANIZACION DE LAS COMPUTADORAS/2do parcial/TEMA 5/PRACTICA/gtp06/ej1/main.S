//Completa los espacios del siguiente código base:
.equ GPIO_ENABLE_REG, 0x60004020
.equ GPIO_OUT_W1TS_REG, 0x60004008
.equ LED_GPIO, 2

.section .text
.global _start
_start:

/* 1. Habilitar GPIO2 como salida */
li a0, GPIO_ENABLE_REG
li a1, (1 << LED_GPIO)
sw a1, 0(a0)

/* 2. Encender LED */
li a0, 0x60004008
li a1, (1 << LED_GPIO)
sw a1, 0(a0)

b. ¿Qué valor debe tener LED_GPIO si el LED está en GPIO2?
2

c. ¿Por qué usamos GPIO_OUT_W1TS_REG en lugar de GPIO_OUT_REG?
Usamos GPIO_OUT_W1TS_REG porque permite poner en HIGH solo el bit del GPIO indicado sin modificar el resto de los pines.
En cambio, GPIO_OUT_REG sobrescribe todo el registro y puede alterar otros GPIOs que estén en uso.
El registro W1TS realiza una operación segura y atómica.

