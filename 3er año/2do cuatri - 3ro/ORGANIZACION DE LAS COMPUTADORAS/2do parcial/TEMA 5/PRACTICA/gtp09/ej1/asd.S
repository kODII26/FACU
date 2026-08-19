Programa: Eco UART con control de LEDs (estilo cátedra)
------------------------------------------------------
- Usa las funciones:
    uart_send(a0)    -> envía 1 carácter por UART0
    uart_receive()   -> devuelve carácter recibido en a0 (0 si no hay dato)
    uart_puts(a0)    -> envía string ASCII terminado en 0

- Comportamiento:
    * LED Verde (GPIO2): se enciende cuando se recibe letra MAYÚSCULA (A-Z)
    * LED Rojo  (GPIO3): se enciende cuando se recibe letra minúscula (a-z)
    * Ambos LEDs se apagan cuando se recibe un dígito (0-9)
    * Otros caracteres: no modifican los LEDs
    * Siempre hace ECO: reenvía el mismo carácter recibido
    * Al iniciar envía: "Sistema Eco Listo"
*/

    .section .rodata
msg_inicio:
    .asciz "Sistema Eco Listo"     # Mensaje de inicio (sin \n, sin \r)

    .section .text

    .global main
    .extern uart_send
    .extern uart_receive
    .extern uart_puts

# =========================
# Direcciones GPIO (ESP32-C3)
# =========================
.equ GPIO_BASE,               0x60004000

.equ GPIO_ENABLE_W1TS_REG,    0x0024      # Habilitar como salida (write 1 to set)
.equ GPIO_OUT_W1TS_REG,       0x0008      # Encender (write 1 to set)
.equ GPIO_OUT_W1TC_REG,       0x000C      # Apagar  (write 1 to clear)

# =========================
# Máscaras de LEDs
# =========================
.equ GPIO_VERDE_MASK,   (1 << 2)          # LED verde  en GPIO2
.equ GPIO_ROJO_MASK,    (1 << 3)          # LED rojo   en GPIO3
.equ GPIO_LEDS_MASK,   (GPIO_VERDE_MASK | GPIO_ROJO_MASK)

# ==================================================
# main:
#   - Configura GPIO2 y GPIO3 como salidas
#   - Apaga ambos LEDs
#   - Envía mensaje inicial por UART
#   - Bucle infinito de eco + control de LEDs
# ==================================================
main:
    # ------------------------------
    # Configurar GPIO2 y GPIO3 como SALIDA
    # ------------------------------
    li      t0, GPIO_BASE
    addi    t0, t0, GPIO_ENABLE_W1TS_REG
    li      t1, GPIO_LEDS_MASK
    sw      t1, 0(t0)                     # Habilita GPIO2 y GPIO3 como salidas

    # ------------------------------
    # Apagar LEDs al inicio
    # ------------------------------
    li      t0, GPIO_BASE
    addi    t0, t0, GPIO_OUT_W1TC_REG
    li      t1, GPIO_LEDS_MASK
    sw      t1, 0(t0)

    # ------------------------------
    # Enviar mensaje inicial por UART
    # a0 = dirección del string
    # ------------------------------
    la      a0, msg_inicio
    call    uart_puts                      # uart_puts("Sistema Eco Listo")

# ============================
# BUCLE PRINCIPAL:
#   - Espera carácter válido
#   - Lo reenvía (eco)
#   - Ajusta LEDs según tipo
# ============================
loop_principal:

    # ------------------------------
    # Esperar hasta recibir un carácter != 0
    # (uart_receive devuelve 0 si no hay dato)
    # ------------------------------
esperar_caracter:
    call    uart_receive                  # a0 = carácter o 0
    beq     a0, x0, esperar_caracter      # si no hay dato, sigo esperando

    # Guardar el carácter en t0 (para reutilizarlo)
    mv      t0, a0

    # ------------------------------
    # ECO: reenviar el mismo carácter recibido
    # ------------------------------
    mv      a0, t0
    call    uart_send                     # uart_send(c)

    # ------------------------------
    # Clasificación del carácter:
    #   1) Dígito '0'..'9'  -> apagar ambos LEDs
    #   2) Mayúscula 'A'..'Z' -> verde ON, rojo OFF
    #   3) Minúscula 'a'..'z' -> rojo ON, verde OFF
    #   4) Otro -> no cambia LEDs
    # ------------------------------

    # ---- ¿Es dígito? ('0'..'9') ----
    li      t1, '0'
    blt     t0, t1, check_mayuscula       # si c < '0' -> no dígito
    li      t2, '9' + 1                   # límite superior exclusivo ('9'+1)
    bge     t0, t2, check_mayuscula       # si c >= '9'+1 -> no dígito

    # Aquí: '0' <= c <= '9'  -> apagar ambos LEDs
    li      t3, GPIO_BASE
    addi    t3, t3, GPIO_OUT_W1TC_REG
    li      t4, GPIO_LEDS_MASK
    sw      t4, 0(t3)
    j       loop_principal

check_mayuscula:
    # ---- ¿Es mayúscula? ('A'..'Z') ----
    li      t1, 'A'
    blt     t0, t1, check_minuscula       # si c < 'A' -> no mayúscula
    li      t2, 'Z' + 1                   # límite superior exclusivo
    bge     t0, t2, check_minuscula       # si c >= 'Z'+1 -> no mayúscula

    # Aquí: 'A' <= c <= 'Z'  -> encender VERDE, apagar ROJO
    # Apagar ROJO
    li      t3, GPIO_BASE
    addi    t3, t3, GPIO_OUT_W1TC_REG
    li      t4, GPIO_ROJO_MASK
    sw      t4, 0(t3)

    # Encender VERDE
    li      t3, GPIO_BASE
    addi    t3, t3, GPIO_OUT_W1TS_REG
    li      t4, GPIO_VERDE_MASK
    sw      t4, 0(t3)

    j       loop_principal

check_minuscula:
    # ---- ¿Es minúscula? ('a'..'z') ----
    li      t1, 'a'
    blt     t0, t1, fin_clasificacion     # si c < 'a' -> no minúscula
    li      t2, 'z' + 1                   # límite superior exclusivo
    bge     t0, t2, fin_clasificacion     # si c >= 'z'+1 -> no minúscula

    # Aquí: 'a' <= c <= 'z'  -> encender ROJO, apagar VERDE
    # Apagar VERDE
    li      t3, GPIO_BASE
    addi    t3, t3, GPIO_OUT_W1TC_REG
    li      t4, GPIO_VERDE_MASK
    sw      t4, 0(t3)

    # Encender ROJO
    li      t3, GPIO_BASE
    addi    t3, t3, GPIO_OUT_W1TS_REG
    li      t4, GPIO_ROJO_MASK
    sw      t4, 0(t3)

    j       loop_principal

fin_clasificacion:
    # No es dígito, ni mayúscula, ni minúscula:
    # no se modifica el estado actual de los LEDs.
    j       loop_principal