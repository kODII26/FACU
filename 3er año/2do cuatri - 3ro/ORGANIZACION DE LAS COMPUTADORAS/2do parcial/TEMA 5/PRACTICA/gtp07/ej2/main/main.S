/* 
Flanco de bajada o sea quiero que cuando GPIO05 pase de 1 a 0
el led en GPIO04 alterne 
*/
.global gpio_irq_init
.global gpio_isr

# ========= EQU =========
.equ GPIO_BASE,                0x60004000
.equ GPIO_ENABLE_W1TS_REG,     0x0024
.equ GPIO_ENABLE_W1TC_REG,     0x0020
.equ GPIO_OUT_REG,             0x0004
.equ GPIO_OUT_W1TS_REG,        0x0008
.equ GPIO_OUT_W1TC_REG,        0x000C
.equ GPIO_STATUS_REG,          0x0038
.equ GPIO_STATUS_W1TC_REG,     0x003C

# Controlador de interrupciones (del PDF)
.equ INTR_MAP_BASE, 0x6000F000
.equ INTERRUPT_CORE0_CPU_INT_ENABLE_REG, (INTR_MAP_BASE + 0x0104)
.equ INTERRUPT_CORE0_CPU_INT_CLEAR_REG, (INTR_MAP_BASE + 0x010C)
.equ INTERRUPT_CORE0_CPU_INT_TYPE_REG, (INTR_MAP_BASE + 0x0108)
.equ CPU_INT_ID, 10 # Canal de interrupción del CPU elegido
.equ GPIO_BTN_NUM, 3 # Pin GPIO para el botón
.equ GPIO_LED_NUM, 1 # Pin GPIO para el LED

.equ GPIO4_MASK, (1 << 4) # LED -> SALIDA
.equ GPIO5_MASK, (1 << 5)


# ===========================================
#   INICIALIZACIÓN
# ===========================================

gpio_irq_init:
 #  Configurar  entrada

 li t0, GPIO_BASE
 addi t0,t0, GPIO_ENABLE_W1TC_REG
 li t1, GPIO5_MASK
 sw t1,0(t0)
 # Configurar salida (LED)

 li t0, GPIO_BASE
 addi t0,t0, GPIO_ENABLE_W1TS_REG
 li t1, GPIO4_MASK
 sw t1,0(t0)

 # ---- Habilitar interrupción en CPU ----
 li t1, (1 << CPU_INT_ID)                 # habilito el canal elegido
 li t0, INTR_MAP_BASE
 addi t0, t0, INTERRUPT_CORE0_CPU_INT_ENABLE_REG
 sw t1, 0(t0)

 # ---- Configurar tipo: flanco ----
 li t0, INTR_MAP_BASE
 addi t0, t0, INTERRUPT_CORE0_CPU_INT_TYPE_REG
 sw t1, 0(t0)       

ret

gpio_isr: 
 # --- Leer estado de interrupciones GPIO ---
 li t0, GPIO_BASE
 addi t0,t0, GPIO_STATUS_REG
 lw t1,0(t0)

 # --- Verificar si GPIO5 fue quien disparó la interrupción ---
 li t2, GPIO5_MASK
 and t3,t1,t2
 beq t3,x0,salir_isr
 
 # --- Alternar LED (GPIO4 HIGH) ---
 li t5, GPIO_BASE
 addi t5,t5,GPIO_OUT_REG
 lw t6,0(t5)
 and t7,t6,GPIO4_MASK 
 beq t7,x0, prender_led
 //si no es cero, lo tengo q apagar:
 li t5, GPIO_BASE 
 addi t8,t5, GPIO_OUT_W1TC_REG
 li t9, GPIO4_MASK
 sw t9,0(t8)
 
 # --- Limpiar interrupción de GPIO5 ---
 li t7, GPIO5_MASK                       # máscara de GPIO5
 li t8, GPIO_BASE
 addi t8, t8, GPIO_STATUS_W1TC_REG       # dirección STATUS_W1TC
 sw t7, 0(t8)                             # limpio interrupción de GPIO5 (Write 1 to clear)
 
 # --- Limpiar interrupción a nivel CPU (canal 10) ---
 li t0, INTR_MAP_BASE                    # t0 = parte alta INT_CLEAR
 addi t0, t0, INTERRUPT_CORE0_CPU_INT_CLEAR_REG  # dirección completa
 li t1, (1 << CPU_INT_ID)                # t1 = bit10
 sw t1, 0(t0)                             # limpia canal 10

prender_led:
 li t0, GPIO_BASE
 addi t0,t0,GPIO_OUT_W1TS_REG
 li t1, GPIO4_MASK
 sw t1,0(t0)

salir_isr:
 mret