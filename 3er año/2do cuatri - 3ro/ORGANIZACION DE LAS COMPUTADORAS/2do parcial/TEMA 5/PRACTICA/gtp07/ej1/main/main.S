/*
pulsador en GPIO6 -> entrada
LEDs en GPIO02-05 -> salidas
al detectar gesto mostrar patron binario 1010 en leds , gpio02 lsb
*/

.section .text
.equ GPIO_BASE_ADDR, 0x60004000 # Dirección base periférico GPIO
.equ GPIO_ENABLE_REG, 0x0020 # Offset registro ENABLE
.equ GPIO_ENABLE_W1TS_REG, 0x0024
.equ GPIO_ENABLE_W1TC_REG, 0x0028 
.equ GPIO_OUT_REG, 0x0004 # Offset registro OUTPUT
.equ GPIO_OUT_W1TS_REG, 0x0008 # Offset registro SET (poner a 1)
.equ GPIO_OUT_W1TC_REG, 0x000C # Offset registro CLEAR (poner a 0)
.equ GPIO_IN_REG, 0x003C # Offset del registro de entrada
.equ GPIO2_MASK, (1 << 2) # Máscara para GPIO2 (salida LED)
.equ GPIO3_MASK, (1 << 3) # Máscara para GPIO3 (salida LED)
.equ GPIO4_MASK, (1 << 4) # Máscara para GPIO4 (salida LED)
.equ GPIO5_MASK, (1 << 5) # Máscara para GPIO5 (salida LED)
.equ GPIO6_MASK, (1 << 6) # Máscara para GPIO6 (entrada del pulsador)

// paso 1: configurar GPIO

.global main
.global main_loop

main:
 # Configuro los 4 led como salidas (GPIO2-GPIO5)
 li t0, GPIO_BASE_ADDR # t0 = 0x60004000
 addi t0, t0, GPIO_ENABLE_W1TS_REG # t0 = 0x60004020
 li t1, (GPIO2_MASK | GPIO3_MASK | GPIO4_MASK | GPIO5_MASK)
 sw t1, 0(t0) # Habilitar GPIO2-5 como salida

 # Configuro GPIO6 como entrada (pulsador)
 li t0, GPIO_BASE_ADDR # t0 = 0x60004000
 addi t0, t0, GPIO_ENABLE_W1TC_REG # t0 = 0x60004020
 li t1, GPIO6_MASK
 sw t1, 0(t0) # Habilitar GPIO6 como entrada
ret # Retornar a C
 
main_loop:
 li t0, GPIO_BASE_ADDR 
 addi t0, t0, GPIO_IN_REG # t0 = dirección del registro de entrada
 lw t1, 0(t0) # Leer el estado del pulsador
 and t2, t1, GPIO6_MASK # Si t1=1 y mask=1 -> pulsador presionado
 beq t2,x0,main_loop # si no está presionado, seguir esperando
 /*  Cuando se presiona -> mostrar patrón 1010 */
 // apago 2 y 4 , prendo 3 y 5 
 li t0, GPIO_BASE_ADDR
 addi t0, t0, GPIO_OUT_W1TC_REG
 li t1, (GPIO2_MASK | GPIO4_MASK)
 sw t1, 0(t0)

 li t0, GPIO_BASE_ADDR
 addi t0,t0, GPIO_OUT_W1TS_REG
 li t1, (GPIO3_MASK | GPIO5_MASK)
 sw t1,0(t0)

esperar_liberacion:
 li t0, GPIO_BASE_ADDR
 addi t0,t0,GPIO_IN_REG
 lw t1,0(t0)
 and t2,t1,GPIO6_MASK
 bne t2,x0,esperar_liberacion // Si el boton no es cero, seguir esperando
 j main_loop



