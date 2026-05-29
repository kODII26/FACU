% zplane dibuja los polos y los ceros en el plano Z
pkg load signal

a= [1 1.7 0.8 -0.1]; % son los productos desarrollados

b= [1 -2 2 -1];

disp('Polos: ');
roots(a)
% viendo los polos podemos concluir que el sistema es estable (ya que son menores a 1) y la respuesta al impulso
% oscila (ya que son complejos)
disp('Ceros: ');
roots(b)


figure
zplane(b,a)
grid on

figure
impz(b,a)
grid on
