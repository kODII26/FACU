 .section .data
numero1:        .word   8
numero2:        .word   5
resultadoSuma:  .word   0

    .section .text
    .global _start

_start:

    # --- cargar numero1 ---
    la  t0, numero1        # t0 ← dirección de numero1
    lw  t1, 0(t0)          # t1 ← valor de numero1

    # --- cargar numero2 ---
    la  t2, numero2        # t2 ← dirección de numero2
    lw  t3, 0(t2)          # t3 ← valor de numero2

    # --- suma ---
    add t4, t1, t3         # t4 = t1 + t3

    # --- guardar resultado en memoria ---
    la  t5, resultadoSuma  # t5 ← dirección de resultadoSuma
    sw  t4, 0(t5)

fin:
    j fin                  # bucle infinito (no existe exit)
