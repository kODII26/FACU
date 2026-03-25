a. Carga dos números en registros (ej. a5 = 4, a6 = 6).

b. Multiplicalos y guarda el resultado en a7.

c. Completa los espacios del siguiente código base:
li a5, 4
li a6, 6
mul a7, a5, a6

d. ¿Cuántos ciclos de reloj toma la multiplicación en el ESP32-C3?
1 ciclo de reloj
e. ¿Qué ocurre si los números son muy grandes (ej. > 32 bits)?
El ESP32-C3 (RV32) trabaja con:

registros de 32 bits

operaciones ALU de 32 bits

Entonces, si los valores a multiplicar exceden los 32 bits:

❌ No pueden cargarse en un registro
❌ No pueden ser procesados por la ALU
❌ La operación dará overflow silencioso (se descartan los bits altos)

En pocas palabras:

⭐ El resultado se recorta a 32 bits, perdiendo los bits superiores.
