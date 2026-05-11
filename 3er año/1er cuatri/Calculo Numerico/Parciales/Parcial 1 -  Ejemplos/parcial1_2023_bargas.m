clc;clear;format long;


%----------------------PREGUNTA 2---------------------------------------------

%z=@(t) ((0.04)*(sqrt(a+t))*(1-t)) - ((t)*(sqrt(3*a)));
%reemplazamos t por t=0.02
% t=((0.04)*(sqrt(a+t))*(1-t)) - ((t)*(sqrt(3*a)));
% 0= ((0.04)*(sqrt(a+t))*(1-t)) - ((t)*(sqrt(3*a))) - t;
%entonces ahora si podemos definir la nueva funcion z con t=0.02
t=0.02;
z2=@(a) ((0.04).*(sqrt(a+t)).*(1-t)) - ((t).*(sqrt(3*a))) - t;

%encontrar a tal que z(t) posea un punto fijo en t=0.02
%ayuda sabemos que la grafica z(t) pasa cerca de w(t)
w=@(t) ( (0.04).*(sqrt(19+t)).*(1-t)) - ( (t).*(sqrt(57)));
%Podemos ver que el valor es aproximadamente 19

figure(1)
xx=linspace(0,50,201);
plot(xx,z2(xx),'r-')
hold on;
plot(xx,y=zeros(size(xx)),'black-')
legend("FUNCION Z2")

figure(2)
plot(xx,w(xx),'b-')
legend("FUNCION W CON T=0.02")

[pBis, rhBis, itBis, tBis] = biseccion(z2, 0, 25, 1000, 1e-6);
pBis

%comprobamos que tiene un punto fijo en t=0.02
a=pBis;
%z=@(t) ((0.04)*(sqrt(a+t))*(1-t)) - ((t)*(sqrt(3*a)));
%  -((t)*(sqrt(3*a))) = ((0.04)*(sqrt(a+t))*(1-t))
% t =  ((0.04)*(sqrt(a+t))*(1-t)) / -(sqrt(3*a))
g=@(t) (((0.04)*(sqrt(a+t))*(1-t)))/ -(sqrt(3*a));

[x, rh, t] = puntofijo(g, 0, 1000, 1e-6);
x

%Buscamos la raiz de la z original
a=pBis;
z=@(t) ((0.04).*(sqrt(a+t)).*(1-t)) - ((t).*(sqrt(3*a)));
[p, rh, it, t] = biseccion(z, 0, 10, 10000, 1e-6);
p


%----------------------PREGUNTA 4---------------------------------------------



%----------------------PREGUNTA 6-------------------------------------------
##f=@(x) sin(x)+cos(1+x.^2)-1;
##
##figure(3)
##
##xx=linspace(6,9,201);
##y = zeros(size(xx));
##plot(xx,f(xx),'b-')
##hold on;
##plot(xx, y, 'r-');
##
##[raiz, rh2Bis, it2Bis, t2Bis] = biseccion(f, 7.8, 8, 1000, 1e-6);
##disp("La raiz mas cercana a 8 es:")
##raiz

