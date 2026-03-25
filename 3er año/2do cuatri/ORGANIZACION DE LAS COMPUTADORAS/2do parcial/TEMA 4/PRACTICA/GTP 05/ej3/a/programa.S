.section .text
.global _start

_start:
    addi t0, x0, 21      # Valor inicial: 21 (0b10101)
    addi t1, x0, 0       # Contador = 0

loop:
    andi t2, t0, 1       # Extrae el bit menos significativo
    add  t1, t1, t2      # Suma ese bit al contador
    srli t0, t0, 1       # Corre 1 bit a la derecha
    bne  t0, x0, loop    # Repite hasta que t0 quede en 0

fin:
    j fin        