  # Archivo: Interrupciones.S
# Configuración de GPIO e interrupciones para ESP32-C3
# LED en GPIO2 - Botón en GPIO3
# LED encendido inicialmente, se apaga cuando se pulsa el botón

.section .text

# --- Constantes para registros del ESP32-C3 ---

# Base addresses
.equ GPIO_BASE,          0x60004000
.equ IO_MUX_BASE,        0x60009000

# GPIO registers offsets
.equ GPIO_OUT_REG,       0x0004
.equ GPIO_OUT_W1TS_REG,  0x0008
.equ GPIO_OUT_W1TC_REG,  0x000C
.equ GPIO_ENABLE_REG,    0x0020
.equ GPIO_IN_REG,        0x003C
.equ GPIO_STATUS_REG,    0x0044 
.equ GPIO_STATUS_W1TC_REG, 0x0048 

# IO MUX registers
.equ IO_MUX_GPIO2_REG,   0x000C 
.equ IO_MUX_GPIO3_REG,   0x0010 

# --- Configuración de GPIO ---
.global configurar_gpio_assembler
.type configurar_gpio_assembler, @function

configurar_gpio_assembler:
    # Prologo
    addi sp, sp, -16
    sw ra, 12(sp)
    
    # --- Configurar GPIO2 como salida (LED) ---
    
    # 1. Configurar función GPIO en IO_MUX para GPIO2
    li t0, IO_MUX_BASE
    lw t1, IO_MUX_GPIO2_REG(t0)
    
    # Limpiar bits de función (MCU_SEL)
    li t2, 0x700
    not t2, t2
    and t1, t1, t2
    
    li t2, 0x100
    or t1, t1, t2
    sw t1, IO_MUX_GPIO2_REG(t0)
    
    # 2. Habilitar GPIO2 como salida
    li t0, GPIO_BASE
    lw t1, GPIO_ENABLE_REG(t0)
    li t2, (1 << 2)
    or t1, t1, t2
    sw t1, GPIO_ENABLE_REG(t0)
    
    # 3. ENCENDER LED inicialmente (GPIO2 a 1)
    li t1, (1 << 2)
    sw t1, GPIO_OUT_W1TS_REG(t0)
    
    # --- Configurar GPIO3 como entrada con pull-up (Botón) ---
    
    # 1. Configurar función GPIO en IO_MUX para GPIO3
    li t0, IO_MUX_BASE
    lw t1, IO_MUX_GPIO3_REG(t0)
    
    # Limpiar bits de función
    li t2, 0x700
    not t2, t2
    and t1, t1, t2
    
    li t2, 0x180
    or t1, t1, t2
    
    # Deshabilitar pull-down
    li t2, (1 << 6)
    not t2, t2
    and t1, t1, t2
    
    sw t1, IO_MUX_GPIO3_REG(t0)
    
    # 2. Deshabilitar GPIO3 como salida (solo entrada)
    li t0, GPIO_BASE
    lw t1, GPIO_ENABLE_REG(t0)
    li t2, (1 << 3)
    not t2, t2
    and t1, t1, t2
    sw t1, GPIO_ENABLE_REG(t0)
    
    # Epilogo
    lw ra, 12(sp)
    addi sp, sp, 16
    ret

# --- Configuración de Interrupciones ---
.global configurar_interrupciones_assembler
.type configurar_interrupciones_assembler, @function

configurar_interrupciones_assembler:
    # Prologo
    addi sp, sp, -16
    sw ra, 12(sp)
    
    # 1. Limpiar cualquier estado de interrupción previo
    li t0, GPIO_BASE
    li t1, (1 << 3)
    sw t1, GPIO_STATUS_W1TC_REG(t0)
    
    # 2. Configurar tipo de interrupción (flanco de bajada)
    li t0, GPIO_BASE
    lw t2, 0x44(t0)
    
    # Limpiar configuración previa (bits 9-11)
    li t3, 0xE00
    not t3, t3
    and t2, t2, t3
    
    # Establecer flanco de bajada (0x2 << 9)
    li t3, 0x400
    or t2, t2, t3
    sw t2, 0x44(t0)
    
    # 3. Habilitar interrupción para GPIO3
    lw t2, 0x40(t0)
    li t3, (1 << 3)
    or t2, t2, t3
    sw t2, 0x40(t0)
    
    # 4. Configurar handler de interrupción
    la t0, gpio_interrupt_handler
    csrw mtvec, t0
    
    # Epilogo
    lw ra, 12(sp)
    addi sp, sp, 16
    ret

# --- Habilitar Interrupciones Globales ---
.global habilitar_interrupciones_assembler
.type habilitar_interrupciones_assembler, @function

habilitar_interrupciones_assembler:
    # Prologo
    addi sp, sp, -16
    sw ra, 12(sp)
    
    # Habilitar interrupciones machine externas
    li t0, 0x800
    csrs mie, t0
    
    # Habilitar interrupciones globalmente
    li t0, 0x8
    csrs mstatus, t0
    
    # Epilogo
    lw ra, 12(sp)
    addi sp, sp, 16
    ret

# --- Handler de Interrupción de GPIO ---
.global gpio_interrupt_handler
.type gpio_interrupt_handler, @function

gpio_interrupt_handler:
    # Prologo - guardar registros
    addi sp, sp, -64
    sw ra, 60(sp)
    sw t0, 56(sp)
    sw t1, 52(sp)
    sw t2, 48(sp)
    sw a0, 44(sp)
    sw a1, 40(sp)
    
    # Verificar si es interrupción externa
    csrr t0, mcause
    li t1, 0x80000000
    and t2, t0, t1
    beqz t2, fin_interrupt
    
    # Verificar código de excepción
    li t1, 0x7FFFFFFF
    and t0, t0, t1
    li t1, 11
    bne t0, t1, fin_interrupt
    
    # Leer estado de interrupciones de GPIO
    li t0, GPIO_BASE
    lw t1, GPIO_STATUS_REG(t0)
    
    # Verificar si es GPIO3
    li t2, (1 << 3)
    and t2, t1, t2
    beqz t2, fin_interrupt
    
    # --- APAGAR LED cuando se presiona el botón ---
    li t0, GPIO_BASE
    li t1, (1 << 2)
    sw t1, GPIO_OUT_W1TC_REG(t0)

limpiar_interrupcion:
    # Limpiar flag de interrupción
    li t0, GPIO_BASE
    li t1, (1 << 3)
    sw t1, GPIO_STATUS_W1TC_REG(t0)

fin_interrupt:
    # Epilogo - restaurar registros
    lw a1, 40(sp)
    lw a0, 44(sp)
    lw t2, 48(sp)
    lw t1, 52(sp)
    lw t0, 56(sp)
    lw ra, 60(sp)
    addi sp, sp, 64
    
    # Retornar de interrupción
    mret

# --- Función para leer estado del botón ---
.global leer_boton_assembler
.type leer_boton_assembler, @function

leer_boton_assembler:
    li t0, GPIO_BASE
    lw t1, GPIO_IN_REG(t0)
    li t2, (1 << 3)
    and a0, t1, t2
    snez a0, a0
    ret