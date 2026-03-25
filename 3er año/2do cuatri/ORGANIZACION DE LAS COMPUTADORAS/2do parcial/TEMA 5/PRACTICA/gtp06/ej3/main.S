a. Cargar dos valores en registros (ej. a0 = 5, a1 = 7).
li a0, 5
li a1,7

b. Sumalos y guarda el resultado en a2.
add a2,a0,a1

c. El resultado se debe mostrar en un arreglo de leds.

/* a2 contiene el resultado de la suma */
/* Queremos escribir ese valor directamente en los LEDs */

/* 1. Habilitar GPIO0–GPIO3 como salida */
li t0, 0x60004000           # GPIO_BASE
addi t0, t0, 0x20           # GPIO_ENABLE_REG
li t1, 0b1111               # LEDs en GPIO0-3
sw t1, 0(t0)

/* 2. Apagar todos los LEDs */
li t0, 0x60004000
addi t0, t0, 0x0C           # GPIO_OUT_W1TC_REG
li t1, 0b1111               # máscara LEDs
sw t1, 0(t0)

/* 3. Encender LEDs indicados por los bits de a2 */
li t0, 0x60004000
addi t0, t0, 0x08           # GPIO_OUT_W1TS_REG
sw a2, 0(t0)                # usar el valor completo de a2 como máscara


d. Completa los espacios del siguiente código base:
li a0, 5
li a1, 7
add a2, a0, a1


e. ¿Qué pasaría si usamos a0 como destino en lugar de a2?