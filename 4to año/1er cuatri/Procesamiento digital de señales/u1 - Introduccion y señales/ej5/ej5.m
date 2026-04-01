addpath('../Funciones creadas');
t_inicial=0;
t_final=2;
fs=4000;
fm=129;
phi=pi/4;

[y,t]= generar_senoidal(fs,fm,phi,t_inicial,t_final);
plot(t,y)

# Tener fs de 4000Hz indica que tiene que dar 4000 ciclos por segundo
# Sin embargo viendo el grafico vemos aproximadamente 2 ciclos por segundo
# Por lo tanto estamos viendo una senoidal de aproximadamente 1Hz
# Es mucho menor a la frecuencia original, y esto tiene sentido teorico ya que
# No se cumple la condicion de 2fs <= fm . Para ver el potencial de la frecuencia original
# Deberiamos tener un fm de almenos 8000

