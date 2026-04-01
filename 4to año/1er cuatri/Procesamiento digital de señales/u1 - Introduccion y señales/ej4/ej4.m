addpath('../Funciones creadas');
fm= [100,25,10,4,1,0.5];
fs=5;
t_i=0;
t_f=1;
phi=pi/4;

for i=1:length(fm)
  [y, t] = generar_senoidal(fs, fm(i), phi, t_i, t_f);
  subplot(3,2,i)
  plot(t, y)
  title(['fm = ', num2str(fm(i)), ' Hz'])
  xlabel('Tiempo')
  ylabel('Amplitud')
  grid on
end

#la señal original tiene frecuencia de 5hz
# por lo tanto deberian verse 5 ciclos en 1 segundo
# vemos 5 ciclos en las frecuencias de 100,25 y 10 Hz de fm
# en las demas ya no se aprecian, y esto tiene sentido teorico ya que no
# se cumple la condicion de 2fs <= fm

