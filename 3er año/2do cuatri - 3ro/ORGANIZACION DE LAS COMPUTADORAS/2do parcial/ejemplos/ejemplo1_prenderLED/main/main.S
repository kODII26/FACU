.section .text
    .global configurar_gpio_asm
    .global encender_led_asm
    .global apagar_led_asm
    .equ GPIO_BASE_ADDR, 0x60004000 # Dirección base periférico GPIO
    .equ GPIO_ENABLE_REG, 0x0020 # Offset registro ENABLE Sirve solo para decirle al hardware si un pin es ENTRADA o SALIDA.
    .equ GPIO_OUT_REG, 0x0004 # Offset registro OUTPUT
    .equ GPIO_OUT_W1TS_REG, 0x0008 # Offset registro SET (poner a 1) Sirve para poner en 1 (HIGH) ciertos pines.
    .equ GPIO_OUT_W1TC_REG, 0x000C # Offset registro CLEAR (poner a 0)
   
    .equ GPIO1_MASK, (1 << 1) # Máscara para GPIO1
    .equ GPIOn_MASK, (1 << n) # Máscara para GPIOn


/* PASO 1 CONFIGURAR GPIO (decir si va a ser salida o entrada) */ 

configurar_gpio_asm:
 # Calcular dirección del registro GPIO_ENABLE
 li t0, GPIO_BASE_ADDR # t0 = 0x60004000
 addi t0, t0, GPIO_ENABLE_REG # t0 = 0x60004020

 # Preparar valor para habilitar GPIO1
 li t1, GPIO1_MASK # t1 = 0b00000010 (bit 1 en 1)

 # Escribir en registro GPIO_ENABLE
 sw t1, 0(t0) # Habilitar GPIO1 como salida

ret # Retornar a C

/* PASO 2 ENCENDER LED */

encender_led_asm:
 # Calcular dirección del registro SET para enceder GPIO01 (High)
 li t0, GPIO_BASE_ADDR # t0 = 0x60004000
 addi t0, t0, GPIO_OUT_W1TS_REG # t0 = 0x60004008

 # Preparar máscara para GPIO1
 li t1, GPIO1_MASK # Máscara para GPIO1

 # Escribir en registro SET (pone a 1 solo el bit especificado)
 sw t1, 0(t0) # Encender LED en GPIO1

 ret # Retornar a C

/* PASO 3 APAGAR LED */

apagar_led_asm:
 # Calcular dirección del registro CLEAR para apagar GPIO01 (Low)
 li t0, GPIO_BASE_ADDR # t0 = 0x60004000
 addi t0, t0, GPIO_OUT_W1TC_REG # t0 = 0x6000400C

 # Preparar máscara para GPIO1
 li t1, GPIO1_MASK # Máscara para GPIO1

 # Escribir en registro CLEAR (pone a 0 solo el bit especificado)
 sw t1, 0(t0) # Apagar LED en GPIO1

 ret # Retornar a C

 /*
 El registro CLEAR funciona de la siguiente manera: 
 si escribes un 1 en un bit específico, ese bit en el registro 
 de salida (OUTPUT) se pone en 0 (LOW). Los demás bits no se ven 
 afectados. Entonces, al escribir la máscara 0b00000010 
 en el registro CLEAR, estamos apagando el GPIO1 (poniéndolo en LOW).
 /*