/*

Implementa un programa que reciba caracteres por UART0 y los envíe de vuelta
(eco), controlando dos LEDs según el tipo de carácter recibido.
○ Requisitos:
■ LED Verde (GPIO2): Se enciende cuando se recibe una letra
mayúscula (A-Z)
■ LED Rojo (GPIO3): Se enciende cuando se recibe una letra
minúscula (a-z)
■ Ambos LEDs se apagan cuando se recibe un número (0-9)
■ Eco: El sistema debe reenviar el mismo carácter recibido
■ Mensaje inicial: "Sistema Eco Listo" al iniciar

*/

.section .data

mensaje_inicio:
    .asciz "Sistema Eco Listo\r\n"


.section .text

.global uart_send
.global uart_receive
.global uart_puts

.equ UART_BASE,       0x60000000
.equ UART_FIFO_REG,   0x0000
.equ UART_STATUS_REG, 0x001C
.equ UART_CLKDIV_REG, 0x0014
.equ UART_CONF0_REG,  0x0020

.equ GPIO_BASE,        0x60004000
.equ GPIO_ENABLE_REG,  0x0020
.equ GPIO_OUT_W1TS,    0x0008      # poner bits en 1
.equ GPIO_OUT_W1TC,    0x000C      # poner bits en 0

.equ mask_1, (1 << 31) // mascara TX
.equ mask_2, (1 << 30) // mascara RX
.equ LED_VERDE,  (1 << 2)   # GPIO2
.equ LED_ROJO,   (1 << 3)   # GPIO3

# --------- uart_send ---------
uart_send:
    li t0, UART_BASE
    addi t0, t0, UART_STATUS_REG

uart_wait:
    lw t1, 0(t0)
    li t3, mask_1
    and t2, t1, t3
    beq t2, x0, uart_wait

    li t3, UART_BASE
    addi t3, t3, UART_FIFO_REG
    sw a0, 0(t3)
    ret

# --------- uart_receive ---------
uart_receive:
    li t0, UART_BASE
    addi t0, t0, UART_STATUS_REG
    lw t1, 0(t0)

    li t4, mask_2
    and t2, t1, t4
    beq t2, x0, uart_no_data

    li t3, UART_BASE
    addi t3, t3, UART_FIFO_REG
    lw a0, 0(t3)
    ret

uart_no_data:
    li a0, 0
    ret

# --------- uart_puts ---------
uart_puts:
    addi sp, sp, -12
    sw ra, 0(sp)
    sw s0, 4(sp)
    sw s1, 8(sp)

    mv s0, a0        # puntero a string
    li s1, 0         # contador (opcional)

puts_loop:
    lb a0, 0(s0)
    beq a0, x0, puts_end
    call uart_send
    addi s0, s0, 1
    addi s1, s1, 1
    j puts_loop

puts_end:
    lw s1, 8(sp)
    lw s0, 4(sp)
    lw ra, 0(sp)
    addi sp, sp, 12
    ret



main:
  # Configurar GPIO2 y GPIO3 como salida
    jal ra, configurar_gpio

    # Enviar mensaje de inicio por UART
    la  a0, mensaje_inicio
    jal ra, uart_puts # Va a uart_puts con el a0=mensajeinicio

main_loop:
    # Leer un carácter por UART
    jal ra, uart_receive # llama a receive y me queda en a0 el bit guardado
    beq a0, x0, main_loop      # si no hay dato, seguir leyendo hasta recibir un dato (polling)

    mv t0, a0      # guardo el carácter recibido

    mv a0, t0      # lo vuelvo a poner en a0 para enviarlo por UART 
    jal ra, uart_send // tengo que mandar porque la consigna dice con eco, o sea cada cosa q recibo la vuelvo a trasmitir

    //una vez que lo mande, ahora si implemento la logica, o sea proceso y prendo leds segun el caso
    # Procesar tipo de carácter → LEDs
    mv a0, t0
    jal ra, procesar_caracter
    j main_loop

configurar_gpio:
 li t0, GPIO_BASE
 addi t0,t0, GPIO_ENABLE_REG
 li t1, (LED_VERDE | LED_ROJO)
 sw t1,0(t0)
ret

procesar_caracter:
  # Crear stack frame
    addi sp, sp, -8
    sw   ra, 4(sp)
    sw   a0, 0(sp)      # guardar carácter

    lw t1, 0(sp)        # t1 = carácter

    # ----- MAYÚSCULA: 'A' a 'Z' -----
    li t2, 'A'
    blt t1, t2, check_minus // si es menor a A, no es mayus

    li t3, 'Z'
    blt t3, t1, check_minus // si es mayor a Z, no es mayus
    //si no salto es porque estoy en el rango [A,Z]

    # Es mayúscula
    jal ra, apagar_leds
    jal ra, encender_verde
    j fin_proc


check_minus:
    # ----- MINÚSCULA: 'a' a 'z' -----
    li t2, 'a'
    blt t1, t2, check_digit

    li t3, 'z'
    blt t3, t1, check_digit

    # Es minúscula
    jal ra, apagar_leds
    jal ra, encender_rojo
    j fin_proc


check_digit:
    # ----- DÍGITO: '0' a '9' -----
    li t2, '0'
    blt t1, t2, otros

    li t3, '9'
    blt t3, t1, otros

    # Es número
    jal ra, apagar_leds
    j fin_proc

otros:
    # Otros caracteres → no cambiar LEDs
    nop

fin_proc:
    # Restaurar contexto
    lw ra, 4(sp)
    addi sp, sp, 8
    ret

apagar_leds:
 li t0, GPIO_BASE
 addi t0,t0, GPIO_OUT_W1TC
 li t1, (LED_VERDE | LED_ROJO)
 sw t1,0(t0)
ret

encender_verde:
 li t0, GPIO_BASE
 addi t0,t0, GPIO_OUT_W1TS
 li t1, LED_VERDE
 sw t1,0(t0)
ret

encender_rojo:
 li t0, GPIO_BASE
 addi t0,t0, GPIO_OUT_W1TS
 li t1, LED_ROJO
 sw t1,0(t0)
ret



/* explicaciones
EXPLICACION DE PORQUE SE HACE mv t0, a0  Y LUEGO mv a0, t0 (LINEA 119)
Una vez que recibiste el carácter, tenés que:
① Hacer el ECO → llamar a uart_send(a0)
② Procesarlo → llamar a procesar_caracter(a0)
Ambas funciones van a usar a0, y cualquiera de ellas lo puede destruir.
➡️ Por eso lo guardamos en otro registro temporal (t0).
t0 es un registro temporal del caller (vos),
y como no llamamos otra función antes de copiarlo, no se pierde.