clear all; clc;
format long;
addpath("G:/Mi unidad/$Cursado actual/Calculo numerico/Scripts octave")
p = @(x) 230*x.^4 + 18*x.^3 + 9*x.^2 - 221*x - 9;
p2 = @(x) (x+9)/(230*x.^3 + 18*x.^2 + 9*x.^1 - 221);
p3 = @(x) 230*x.^4 + 18*x.^3 + 9*x.^2 - 222*x - 9;
dp3 = @(x) 920*x.^3 + 54*x.^2 + 18*x - 222;
x = linspace(-1,1,1000);
g = @(x) x;
figure(1)
hold on;
plot(x,p3(x),'r-');
plot(x,g(x),'b-');

[x,h,it] = Puntofijo(p2,0,10000,0.5e-6);
x
it

%El primer punto fijo era posible calcularlo utilizando punto fijo y p2
%debido a que la derivada en cercanias es menor en valor abs que 1
%para la segunda podemos calcular la raiz de p3 que seria el equivalente de
%calcular el punto fijo de p
[x,h,it] = Newton(p3,dp3,2,10000,0.5e-6);
x
it

