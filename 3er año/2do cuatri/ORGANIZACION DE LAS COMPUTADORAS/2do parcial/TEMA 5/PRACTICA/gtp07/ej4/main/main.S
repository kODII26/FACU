/*
Desarrolle un contador binario de 4 bits (0-15) mostrado en los LEDs de
GPIO2-GPIO5 (GPIO2 = LSB). El contador debe incrementarse con cada pulsación
del botón en GPIO6, mostrando inmediatamente el nuevo valor en los LEDs. Al
llegar a 15, el contador debe volver a 0 en la siguiente pulsación.

gpio6 -> boton
gpio2-5 -> leds
*/

.global gpio_irq_init

# ========= EQU =========
.equ GPIO_BASE,                0x60004000
.equ GPIO_ENABLE_W1TS_REG,     0x0024
.equ GPIO_ENABLE_W1TC_REG,     0x0020
.equ GPIO_OUT_REG,             0x0004
.equ GPIO_OUT_W1TS_REG,        0x0008
.equ GPIO_OUT_W1TC_REG,        0x000C
.equ GPIO_STATUS_REG,          0x0038
.equ GPIO_STATUS_W1TC_REG,     0x003C
.equ GPIO_IN_REG, 0x003C # Offset del registro de entrada

# ========= MASCARAS =========
.equ GPIO2_MASK, (1 << 2) # LED02
.equ GPIO3_MASK, (1 << 3) # LED03 
.equ GPIO4_MASK, (1 << 4) # LED04
.equ GPIO5_MASK, (1 << 5) # LED05
.equ GPIO6_MASK, (1 << 6) # BOTON


/*
El corrimiento << 2 se usa porque los LEDs no empiezan en el GPIO0, sino en el GPIO2.
Como el LED menos significativo (LSB) está en el GPIO2, el bit b0 del contador debe ubicarse 
en el bit 2 del registro de salida.
Para desplazar un número de modo que su bit0 se ubique en el bit2, se realiza un corrimiento de 2 
posiciones: contador << 2.
*/

gpio_irq_init:
 li t0,GPIO_BASE
 addi t0,t0, GPIO_ENABLE_W1TS_REG
 li t1, (GPIO2_MASK | GPIO3_MASK | GPIO4_MASK | GPIO5_MASK)
 sw t1,0(t0)

 li t0, GPIO_BASE
 addi t0,t0, GPIO_ENABLE_W1TC_REG
 li t1, GPIO6_MASK
 sw t1,0(t0)
 li t3, 0 # contador


controlar_pulsador:
 li t0, GPIO_BASE
 addi t0,t0, GPIO_IN_REG
 lw t1,0(t0)
 and t2,t1, GPIO6_MASK
 beq t2,x0, controlar_pulsador
 // si presionaron tengo que sumar y mostrar el resultado en los leds
 // hago el contador
 addi t3,t3,1
 # si llega a 16 → volver a 0
 li t0, 16
 bne t3, t0, no_reset // el reset tiene que hacerse antes de mostrar. por eso no podria saltar al label reset en vez de no reset
 li t3, 0

no_reset:
 //tengo q mostrar  el valor en los led
 // 1- apago todos
 li t0, GPIO_BASE
 addi t0,t0,GPIO_OUT_W1TC_REG
 li t1, (GPIO2_MASK | GPIO3_MASK | GPIO4_MASK | GPIO5_MASK)
 sw t1,0(t0)
 // 2- desplazo el contador para que cuadre con el led02 en adelante
 slli t1,t3,2
 // 3- muestro el resultado en los led
 li t0,GPIO_BASE
 addi t0,t0,GPIO_OUT_W1TS_REG
 sw t1,0(t0) # t1 tiene el contador desplazado
 
    # ---- ESPERAR HASTA QUE SE SUELTE → clave del polling anti-rebote ----
esperar_suelto:
    li t0, GPIO_BASE
    addi t0,t0, GPIO_IN_REG
    lw t1,0(t0)
    and t2,t1,GPIO6_MASK
    bne t2,x0, esperar_suelto   # mientras esté apretado → esperar

    j controlar_pulsador
 
    