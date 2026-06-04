clc
clear

format long;

disp("EJERCICIO 2");
f=@(x) x + ( exp(-10*x.^2) .* cos(x) )

figure(1)
m2=linspace(-0.327,-0.326,1000);
plot(m2,f(m2));

a2=-0.327;
b2=-0.326;
maxit2=1000;
tol2=1e-6;

[p2, rh2, it2, t2] = biseccion(f, a2, b2, maxit2, tol2);
disp("La raiz de f(x) es : ")
p2

disp("EJERCICIO 3");
g = @(x) sin(x) + cos(1+x.^2)-1;
dg = @(x) (-2 .*x .* sin((x.^2)+1)) + cos(x);
dg2 = @(x) -sin(x)-2*(sin(1+x.^2)+2*x.^2*cos(1+x.^2));

%graficamos
figure(2)
m3 =linspace(7.5,8.5,200);
plot(m3,g(m3),'b')
hold on;
plot(m3,dg(m3),'r')
hold on;
maxit3=1000;
tol3 = 1e-10;
x03 = 8;

%en la grafica vemos que el max esta entre 7.8 y 8
%usamos biseccion con la derivada para ver donde corta a la grafica
%ya que donde la derivada corta a x, hay un max o min
[x3,h3,it3,t3] = biseccion(dg,7.8,8,1000,1e-10);
disp("El valor x mayor cercano a 8 es:")
x3
disp("F(x_max):")
g(x3)

disp("EJERCICIO 5");
A=[1 2 -2 ; 1 1 1 ; 2 2 1];
b=[7;2;5];
x05=b;
tol5=1e-8;
maxit5=1000;

rEspectralGauss = RadioEspectral(A,'gs',0)
disp("Radio > 1 , No converge")
disp("")
[xGauss, rGauss, itGauss, tGauss] = GaussSeidel(A, b, x05, 10000, tol5);

rEspectralJacobi = RadioEspectral(A,'ja',0)
disp("Radio < 1, Converge")
disp("")
[xJac,rJac,itJac] = Jacobi(A,b,x05,maxit5,tol5);

disp("El w optimo es : ")
[wopt] = w_optimo(A,b)
%wopt = 0.250000000000000
disp("")

rEspectralSOR = RadioEspectral(A,'sor',wopt)
disp("Radio < 1, Converge")
[xSor, rhSor, itSor, tSor] =sor(A, b, b, 1000, tol5, 0.4);
itSor









