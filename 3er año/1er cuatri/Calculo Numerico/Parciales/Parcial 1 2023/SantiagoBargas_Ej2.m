clc;
clear;
format long;
%punto fijo es
t=0.02;

z=@(a) 0.04 * ( sqrt(a+t).*(1-t) ) -t.*sqrt(3*a) - t;
w=@(t) 0.04 * ( sqrt(19+t).*(1-t) ) - t.*sqrt(57);
%sabemos que a es cercano a 19 por la funcion w

figure(1)
m=linspace(0,1,100);
plot(m,z(m),'b');


tol=1e-6;
[valorA, rh, it, t] = biseccion(z, 18, 22, 1000, tol);
[xA, rh2, it2, t2] = secante(z, 18, 22, 1000, tol);
disp("El valor de A es:")
valorA
xA

%una vez obtenido el valor a redefinimos z, y obtenemos la raiz de z2(t)
%graficamos z2(t)
z2=@(t) 0.04 * ( sqrt(valorA+t).*(1-t) ) -t.*sqrt(3*valorA);
figure(2)
m2=linspace(0,5,1000);
plot(m2,z2(m2),'r');
hold on;
plot(m,w(m),'b');


%observamos dos puntos cercanos a su raiz para tener un intervalo
%y obtenemos la raiz con algun metodo
[xSec, rhSec, itSec, tSec] = secante(z2, 0, 1, 1000, tol);
[xBis, rhBis, itBis, tBis] = biseccion(z2, 0, 1, 1000, tol);
disp("la raiz de z(t) es ")
xSec
xBis





