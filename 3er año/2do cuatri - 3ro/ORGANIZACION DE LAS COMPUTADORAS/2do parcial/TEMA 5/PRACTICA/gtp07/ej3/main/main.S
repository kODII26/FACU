/*
Implemente un semáforo con 3 LEDs (Rojo-GPIO2, Amarillo-GPIO3, Verde-GPIO4)
usando retardos implementados en assembler. La secuencia debe ser:
a. Rojo encendido por 3 segundos
b. Verde encendido por 3 segundos
c. Amarillo encendido por 1 segundo
d. Repetir el ciclo indefinidamente

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

# ========= MASCARAS =========
.equ GPIO2_MASK, (1 << 2) # Rojo
.equ GPIO3_MASK, (1 << 3) # Amarillo 
.equ GPIO4_MASK, (1 << 4) # verde

# ========= DELAYS ========= valores a ojo
.equ DELAY_1S, 50000
.equ DELAY_3S, 150000 # delay3s= 3*delay1s

gpio_irq_init:
 //Configurar salidas
 li t0, GPIO_BASE_ADDR
 addi t0,t0, GPIO_ENABLE_W1TS_REG
 li t1, (GPIO2_MASK | GPIO3_MASK | GPIO4_MASK)
 sw t1,0(t0)

loop:
 //prender rojo 3 seg, apagar verde y amarillo
 li t0, GPIO_BASE_ADDR
 addi t0,t0, GPIO_OUT_W1TS_REG
 li t1, GPIO2_MASK
 sw t1,0(t0)

 li t0, GPIO_BASE_ADDR
 addi t0,t0, GPIO_OUT_W1TC_REG
 li t1, (GPIO3_MASK | GPIO4_MASK)
 sw t1,0(t0)

 li a0, DELAY_3S
 jal ra, delay

 //prender verde 3 seg, apagar rojo y amarillo
 li t0, GPIO_BASE_ADDR
 addi t0,t0, GPIO_OUT_W1TS_REG
 li t1, GPIO4_MASK
 sw t1,0(t0)

 li t0, GPIO_BASE_ADDR
 addi t0,t0, GPIO_OUT_W1TC_REG
 li t1, (GPIO3_MASK | GPIO2_MASK)
 sw t1,0(t0)

 li a0, DELAY_3S
 jal ra, delay

 //prender amarillo 1 seg, apagar verde y rojo
 li t0, GPIO_BASE_ADDR
 addi t0,t0, GPIO_OUT_W1TS_REG
 li t1, GPIO3_MASK
 sw t1,0(t0)

 li t0, GPIO_BASE_ADDR
 addi t0,t0, GPIO_OUT_W1TC_REG
 li t1, (GPIO2_MASK | GPIO4_MASK)
 sw t1,0(t0)

 li a0, DELAY_1S
 jal ra, delay
j loop:

delay: 
 mv t2,a0
delay_loop:
 addi t2,t2,-1
 bnez t2,delay_loop
 ret
 