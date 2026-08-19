.section .text
.equ GPIO_BASE_ADDR, 0x60004000 # Dirección base periférico GPIO
.equ GPIO_ENABLE_REG, 0x0020 # Offset registro ENABLE
.equ GPIO_OUT_REG, 0x0004 # Offset registro OUTPUT
.equ GPIO_OUT_W1TS_REG, 0x0008 # Offset registro SET (poner a 1)
.equ GPIO_OUT_W1TC_REG, 0x000C # Offset registro CLEAR (poner a 0)
.equ GPIO_IN_REG, 0x003C # Offset del registro de entrada
.equ GPIO1_MASK, (1 << 1) # Máscara para GPIO1 (salida LED)
.equ GPIO3_MASK, (1 << 3) # Máscara para GPIO3 (entrada del pulsador)

/* Falta la parte de configurar gpio como salida, que se hace en el ejemplo 1
Para prender un LED sí o sí necesitás que el GPIO sea salida
Siempre, en ESP32-C3 y cualquier micro:
 -Si querés leer un pin → el pin debe ser entrada (ENABLE = 0)
 -Si querés escribir (encender LED) → el pin debe ser salida (ENABLE = 1)
No existe excepción.
*/

leer_pulsador_y_controlar_led_asm:
 li t2, GPIO_BASE_ADDR
 addi t2, t2, GPIO_IN_REG # Dirección de GPIO_IN (lectura de entradas)
 li t3, GPIO3_MASK # Máscara para GPIO3 (botón)

 li t4, GPIO_BASE_ADDR
 addi t4, t4, GPIO_OUT_W1TS_REG # Dirección para SET GPIO1 (encender LED)
 li t5, GPIO_BASE_ADDR
 addi t5, t5, GPIO_OUT_W1TC_REG # Dirección para CLEAR GPIO1 (apagar LED)
 li t6, GPIO1_MASK # Máscara para GPIO1 (LED

loop_pulsador:
 lw t0, 0(t2) # Leer GPIO_IN
 and t1, t0, t3 # t1 = t0 & GPIO3_MASK
 beq t1, x0, apagar_led # Si t1 == 0, botón NO presionado → apagar LED
 sw t6, 0(t4) # Botón presionado → encender LED
 j loop_pulsador

apagar_led:
 sw t6, 0(t5) # Apagar LED
 j loop_pulsador

/*
Esto que acabamos de hacer se llama polling, es una técnica de programación en
la que nuestro microcontrolador revisa constantemente el estado de una 
entrada (pulsador) para saber si ocurrió un evento.
El procesador está ocupado revisando constantemente si el pulsador fue
presionado.
*/ 