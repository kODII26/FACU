.section .text
 .global gpio_irq_init
 .global gpio_isr
 # === DEFINICIONES DE BASES Y REGISTROS ===
 .equ GPIO_BASE, 0x60004000 # Base para registros GPIO
 # Registros para configurar entrada/salida
 .equ GPIO_ENABLE_W1TS_REG, (GPIO_BASE + 0x0024) # Escribir 1 para activar salida (Set)
 .equ GPIO_ENABLE_W1TC_REG,(GPIO_BASE + 0x0020) # Escribir 1 para desactivar salida (Clear)
 # Registros para salida de LED
 .equ GPIO_OUT_W1TS_REG,(GPIO_BASE + 0x0008) # Escribir 1 para poner HIGH
 .equ GPIO_OUT_W1TC_REG,(GPIO_BASE + 0x000C) # Escribir 1 para poner LOW
 # Registros de interrupción del GPIO
 .equ GPIO_STATUS_REG, (GPIO_BASE + 0x0038) # Estado de interrupciones pendientes
 .equ GPIO_STATUS_W1TC_REG,(GPIO_BASE + 0x003C) # Limpieza de interrupción (Write‑1‑To‑Clear)
 .equ GPIO_PCPU_INT_REG, (GPIO_BASE + 0x0044) # Interrupciones de GPIO ya “propagadas” al PRO CPU
 # Registros del controlador de interrupciones del CPU / matriz
 .equ INTR_MAP_BASE, 0x6000F000
 .equ INTERRUPT_CORE0_CPU_INT_ENABLE_REG, (INTR_MAP_BASE + 0x0104)
 .equ INTERRUPT_CORE0_CPU_INT_CLEAR_REG, (INTR_MAP_BASE + 0x010C)
 .equ INTERRUPT_CORE0_CPU_INT_TYPE_REG, (INTR_MAP_BASE + 0x0108)
 .equ CPU_INT_ID, 10 # Canal de interrupción del CPU elegido
 .equ GPIO_BTN_NUM, 3 # Pin GPIO para el botón
 .equ GPIO_LED_NUM, 1 # Pin GPIO para el LED
# Máscaras binarias
.equ GPIO_BTN_MASK, (1 << GPIO_BTN_NUM) # 0b00001000 → máscara para GPIO3
.equ GPIO_LED_MASK, (1 << GPIO_LED_NUM) # 0b00000010 → máscara para GPIO1

# ===============================
# INICIALIZACIÓN: GPIO + IRQ
# ===============================
gpio_irq_init:
 # Configurar GPIO3 como entrada
 li t0, GPIO_BTN_MASK # Cargar la máscara del botón en t0
 li t1, GPIO_OUT_W1TC_REG  # Cargar parte alta de la dirección GPIO_ENABLE_W1TC
 ___________________ # t1 ← dirección completa
 sw t0, 0(t1) # Clear bit correspondiente → GPIO3 como entrada
 # Configurar GPIO1 como salida (LED)
 li t0, GPIO_LED_MASK # Cargar la máscara del LED en t0
 ___________________ # Cargar parte alta de la dirección GPIO_ENABLE_W1TS
 li t1, GPIO_ENABLE_W1TS_REG # t1 ← dirección completa
 sw t0,0(t1) # Set bit correspondiente → GPIO1 como salida
 # --- Habilitar canal 10 de interrupción del CPU ---
 li t1, CPU_INT_ID # t1 (bit 10 activado) CPU_INT_ID
 ___________________ # t0 = parte alta de INT_ENABLE
 li t0, INTERRUPT_CORE0_CPU_INT_ENABLE_REG # t0 = dirección completa
 sw t1, 0(t0) # habilita canal 10 del CPU

# --- Configurar tipo de interrupción (flanco) para canal 10 ---
 li t0, INTERRUPT_CORE0_CPU_INT_TYPE_REG # t0 = parte alta de INT_TYPE
 ___________________ # t0 = dirección completa
 ___________________ # tipo: flanco ( 1 = edge-triggered)
 ___________________ # volver de la función de inicialización
# =====================================
# RUTINA DE SERVICIO DE INTERRUPCIÓN (ISR)
# =====================================
gpio_isr:
 # --- Leer estado de interrupciones GPIO ---
 ___________________ # t0 = parte alta de GPIO_STATUS_REG
 ___________________ # t0 = dirección completa
 ___________________ # t1 = contenido del registro de estado (interrupt pending)
 # --- Verificar si GPIO3 fue quien disparó la interrupción ---
 ___________________ # t2 = t1 & GPIO_BTN_MASK → verificar si se activó GPIO3
 ___________________ # si t2 == 0, no fue GPIO3 → salir de la ISR

# --- (Opcional) Leer GPIO_PCPU_INT_REG para confirmar interrupción activa ---
 ___________________ # t3 = parte alta del registro de interrupción CPU
 ___________________ # t3 = dirección completa
 ___________________ # t4 = valor actual (qué GPIO interrumpió al CPU)
 # --- Encender LED (GPIO2 HIGH) ---
 ___________________ # t5 = GPIO_LED_MASK → máscara de GPIO1
 ___________________ # t6 = parte alta de dirección de salida (set)
 ___________________ # t6 = dirección completa
 ___________________ # salida en GPIO2 en HIGH → enciende LED
 # --- Limpiar interrupción de GPIO3 ---
 ___________________ # t7 = GPIO_BTN_MASK → máscara de GPIO3
 ___________________ # t8 = parte alta de STATUS_W1TC
 ___________________ # t8 = dirección completa
 ___________________ # limpia la interrupción del GPIO3 (Write 1 to clear)
 # --- Limpiar interrupción a nivel CPU (canal 10) ---
 ___________________ # t0 = parte alta INT_CLEAR
 ___________________ # t0 = dirección completa
 ___________________ # t1 = 0x400 → bit 10
 ___________________ # limpia interrupción del CPU en canal 10
isr_exit:
 mret # retornar de la interrupción al programa principal mret