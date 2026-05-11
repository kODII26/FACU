clc
clear

format long;

disp("EJERCICIO 1")
f_1=@(x) x + exp(-10*x.^2).*cos(x)
tol=1e-6;
maxit = 100000;
m1=linspace(-1,1,2000);
figure(1);
plot(m1,f_1(m1))

%pide la raiz de f usando biseccion
%graficamos y vemos que la raiz esta entre x=-0.35 y x= -0.3
[p1, rh1, it1, t1] = biseccion(f_1, -0.3265, -0.326, maxit, tol);
disp("La raiz de f_1(x) es : ")
p1

disp("EJERCICIO 2")
f_2=@(x) sin(x)+cos(1+x.^2)-1   %funcion
df_2=@(x)  cos(x) - 2*x.*sin(1+x.^2);  %primer derivada

m2=linspace(0,4,1000);
figure(2);
plot(m2,f_2(m2));
hold on;
plot(m2,df_2(m2));
maxit=1000;
tol=1e-6;

%graficamos la funcion vemos que el maximo esta entre 2 y 2.5
%entonces la derivada cuando corta al eje x va a tener un maximo o minimo
%usamos biseccion entre 2 y 2.5 ya que biseccion devuelve la raiz en un intervalo
[p2, rh2, it2, t2] = biseccion(df_2, 2.2, 2.6, maxit, tol);
disp("El maximo valor x de f(x) es:")
p2

disp("EJERCICIO 4")
A=[0.5  -1  0 ; -1 3 -1; 0 -1 2];
b=[7;4;5];
x0=b;
tol=1e-8;

%[wopt] = w_optimoA(A,b);
%disp("El W optimo es: ")
%wopt

[xG, rG, itG, tG] = GaussSeidel(A, b, x0, maxit, tol);
rGaussSeidel=RadioEspectral(A,'gs',0);
rGaussSeidel %<1 converge
disp("Gauss-Seidel converge en")
itG
disp("iteraciones")
[xJa,rJa,itJa,tJa] = Jacobi(A,b,x0,maxit,tol);
rJacobi=RadioEspectral(A,'ja',0);
rJacobi %<1 converge

