% medicion cada 12 minutos durante 5 horas
% son 26 mediciones en total 5*5+1
% 12min = 0.2h

v = load("datos_velocidades.txt");

t = 0:0.2:5;

A = [sin(2*t') (t'.^2) (2.^t') ones(length(t),1)];

c = A\v;

c1 = c(1);
c2 = c(2);
c3 = c(3);
c4 = c(4)
