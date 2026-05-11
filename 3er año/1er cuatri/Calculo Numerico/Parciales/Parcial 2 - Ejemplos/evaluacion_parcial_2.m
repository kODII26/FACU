clear all; clc;
format long;
##%PREGUNTA 1
##%grado <=4
##
###datos
##x=[0 1 2 3 4 5 6]';
##y=[432 599 1012 1909 2977 4190 5961]';
##
##[PL, L] = Lagrange(x,y);
##plag = @(x) polyval(PL,x);
##
##%b)  Determinar la funcion lineal p1 que mejor aproxima en el sentido
##%de cuadrados mınimos los datos dados (modelo lineal).
##[coef1,A,b] = minimoscuadrados(x,y,1);
##r1 = @(x) coef1(1).*x + coef1(2);
##
##
##%c) Determinar el polinomio p2 de grado ≤ 2 que mejor aproxima
##%en el sentido de cuadrados minimos los datos dados (modelo cuadratico).
##[coef2,A,b] = minimoscuadrados(x,y,2)
##r2 = @(x) coef2(1).*x.^4 + coef2(2).*x.^3 + coef2(3).*x^2+coef2(4).*x+coef2(5);
##


##%Pregunta 2
##%tt=[0.2 0.3 0.4 0.5 0.6 0.7 0.8];
##t=[0.2:0.1:0.8];
##intensidad=[3.16 2.38 1.75 1.34 1.00 0.74 0.56];
##
##%I(t) = I0*e^-u*t   cuanto vale I0 y u? lo buscamos con minimos cuadrados
##
##lc = log(intensidad);
##N=length(t);
##
##[coef,A,b] = minimoscuadrados(t,lc,1); %uno pq es linealizacion
##
##I0=exp(coef(2))
##u=-coef(1)
##%COPIADO DEL EJERCICIO 11 TP 5

%PREGUNTA 3
f = @(x) 2.5 + x.*cos(2*x)
df = @(x) cos(2*x)-2*x.*sin(2*x)

F = @(x) 2*pi*f(x).*sqrt(1+df(x).^2)

a=0;
b=3;
n=3;
L=20;
%RESOLUCION
%cuadratura de gauss con n = 3
Q=cuad_gauss_c(F,a,b,L,n)
Q=cuad_gauss_c(F,a,b,40,n)
Q=cuad_gauss_c(F,a,b,80,n)
Q=cuad_gauss_c(F,a,b,160,n)
disp("Vemos que con L=20 tiene iguales a los demas 128.3703 por tanto 7 cifras exactas");
