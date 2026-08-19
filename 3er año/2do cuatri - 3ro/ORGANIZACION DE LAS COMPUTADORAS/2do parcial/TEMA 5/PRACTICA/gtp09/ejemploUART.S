.section .text

.global uart_send
.global uart_receive
.global uart_puts

.equ UART_BASE, 0x60000000 // direccion UART0 (como gpio_base)
.equ UART_CLKDIV_REG, 0x0014 
.equ UART_FIFO_REG, 0x0000 // registro FIFO para leer/escribir
.equ UART_STATUS_REG, 0x001C // registro de estados (como TX_FULL o RX_EMPTY)
.equ UART_CONF0_REG, 0x0020 

.equ mask_1, (1 << 31) // mascara para el bit 31, o sea para estado de TX
.equ mask_2, (1 << 30) // mascara para el bit 30, o sea para estado de RX
/*
idea central: vamos a leer UART_STATUS_REG y con AND + máscaras mirar esos bits 
para saber si podemos enviar o si hay algo para recibir.
*/

# ESPERAR A QUE EL BUFFER TX ESTE LISTO.
uart_send:
    li t0, UART_BASE
    addi t0, t0, UART_STATUS_REG

    # la forma con lui depende de la cantidad de bits que tenga en la segunda direccion, despues tengo que cargar la palabra con un 
    # offset de la cantidad de bits que necesito cargar de la segunda direccion (4 * cantidad_posiciones_direccion)
    # lui t0, uart_base
    # lw t1, offset(t0) 
    # siendo el offset de uart_status_reg --> 4 * 4 = 16 bits > 12 bits --> no lo puedo referenciar 

    uart_wait:
        lw t1, 0(t0)
        li t3, mask_1
        and t2, t1, t3
        beq t2, x0, uart_wait

    li t3, UART_BASE
    addi t3, t3, UART_FIFO_REG

    sw a0, 0(t3) // guardo a0 en el FIFO para trasmitir, se supone que en a0 tengo el dato a trasmitir
    ret

uart_receive:
    li t0, UART_BASE
    addi t0, t0, UART_STATUS_REG
    lw t1, 0(t0)

    li t4, mask_2
    and t2, t1, t4
    beq t2, x0, uart_no_data
    // si no es cero, hay dato valido para leer
    li t3, UART_BASE
    addi t3, t3, UART_FIFO_REG

    lw a0, 0(t3) // cargo lo que haya leido en el FIFO en a0 
    ret

uart_no_data:
    li a0, 0 // cargo 0 en la palabra a0 
    ret

uart_puts: // enviar string 
    addi sp, sp, -12 // preparo la pila para enviar 

    sw ra, 0(sp) // 4 bits para la direccion de retorno
    sw s0, 4(sp)
    sw s1, 8(sp)

    mv s0, a0 // copia la direccion del string en s0, ahora s0 es nuestro puntero que recorre la cadena
    li s1, 0  # contador para saber la cantidad de caracteres enviados 
    puts_loop:
        lb a0, 0(s0) # carga el proximo byte de la cadena en a0
        beq a0, x0, puts_end # si es cero, se llego al final de la cadena
        // si no es cero: 
        call uart_send // llama a uart_send para enviar el caracter enviar

        addi s0, s0, 1 # avanza el puntero para leer el proximo caracter
        addi s1, s1, 1 # aumenta el contador de caracteres
        j puts_loop

    puts_end: # restaurar 
        lw s1, 8(sp)
        lw s0, 4(sp)
        lw ra, 0(sp)
        addi sp,sp,12
        ret