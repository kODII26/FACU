a. Crea un loop que decrementa un registro hasta cero.


b. Usar bnez (branch if not equal zero) para controlar el loop.
Completa los espacios del siguiente código base :
delay:
li a2, 500000 /* Contador */
loop_delay:
addi a2, a2, -1
bnez a2, loop_delay
ret
c. ¿Cuántos ciclos de reloj tomará aproximadamente este retardo? (Asumiendo 1
ciclo por instrucción).
El retardo tomará aproximadamente 500,000 ciclos de reloj, 
ya que el loop decrementa el contador desde 500,000 hasta 0,
ejecutando una instrucción de resta y una instrucción de bifurcación en 
cada iteración.
d. ¿Cómo modificarías el valor del contador para un parpadeo más rápido?
Para un parpadeo más rápido, puedes reducir el valor inicial del contador.