clc;clear all; format long;

%-------------EJERCICIO 1-------------------------------------------
##disp("EJERCICIO 1")
##f=@(x) x + exp(-10*x.^2).*cos(x)
##tol=1e-6;
##maxit = 100000;
##xx=linspace(-1,1,2000);
##figure(1);
##plot(xx,f(xx))
##hold on;
##plot(xx, y=zeros(size(xx)));
##
##[p, rh, it, t] = biseccion(f, -1, 0, maxit, tol);
##disp("La raiz es: ")
##p

%-------------EJERCICIO 2-------------------------------------------

f=@(x) sin(x)+cos(1+x.^2)-1   %funcion
df=@(x)  cos(x) - 2*x.*sin(1+x.^2);  %primer derivada

xx=linspace(0,4,201);
figure(1);
plot(xx,f(xx),'b-')
hold on;
plot(xx,df(xx),'r-')
plot(xx, y=zeros(size(xx)),'g-');
legend("FUNCION","DERIVADA")

%pide el maximo de la funcion, lo obtenemos con la derivada cuando
%corta al eje x
[p, rh, it, t] = biseccion(df, 2, 2.5, 1000, 1e-6);
disp("El maximo valor de la funcion x es:")
f(p)
disp("En x=")
p
