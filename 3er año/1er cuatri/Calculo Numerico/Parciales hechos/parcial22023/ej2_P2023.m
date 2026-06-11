addpath('Funciones');
clc;
clear all;
format long;


inter=[0,120];
L=120;
I=4250;
P=3000;
E=2.1e6;

h=0.05;
subinter=(120-0)/h;
y0=[0,0];

f=@(x,y) [y(2) ; P*(L-x)/(E*I)*((1+y(2))^2)^1.5];

[t,y]=rk4(f, inter, y0, subinter);
%t posiciones en x
%y(:,1) desplazamiento
%y(:,2) pendiente


[max1,idx] = max(y(:,1)); %recorre toda la columna de y
%y representa desplazamiento, la otra columna es y' que representa pendiente


disp("El maximo desplazamiento es:")
max1

 %para ver la pendiente
posi= t;
poli = polyfit(t',y(:,2),2);
g = @(x) poli(3) + (poli(2).*x) + (poli(1).*x.^2)-0.0019 ;


%una vez graficado ya vemos donde corta en 0 el valor de la pendiente
[x,h] = biseccion(g, 64.3, 64.4, 400, 1e-5);
x
