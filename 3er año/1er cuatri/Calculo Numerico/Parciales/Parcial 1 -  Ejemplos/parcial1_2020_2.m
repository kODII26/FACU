clc
clear

disp("EJERCICIO 1")
f_1=@(x) x+exp(-10*x.^2).*cos(x)
df_1=@(x) 1 - 20*x.*exp(-10*x.^2).*cos(x) - exp(-10*x.^2).*sin(x);
x0=0;
tol_1=1e-6;

m1=linspace(-10,10,1000);
figure(1)
plot(m1,f_1(m1),'r');
hold on;
plot(m1,df_1(m1),'b');
[x1,rh1,it1,t1] = NewtonRaphson(f_1,df_1,x0,1000,tol_1);
disp("Si df(x) se anula en algún punto cercano a la raíz, la aproximación de la tangente se hace infinita y el método puede diverger.")

disp("EJERCICIO 3")
A=[4 2 -2 ; 2 4 2 ; -2 2 4.05];
b=[7 2 5]';
x0_3=b;
tol_3=1e-8;
maxit_3=1000;

[xJac,rJac,itJacobi,tJacobi] = Jacobi(A,b,x0_3,maxit_3,tol_3);
rEspectralJacobi=RadioEspectral(A,'ja',0)
disp("Jacobi converge ya que su radio espectral < 1")

[xGauss, rGauss, itGauss, tGauss] = GaussSeidel(A, b, x0_3, maxit_3, tol_3);
rEspectralGaussSeidel=RadioEspectral(A,'gs',0)
disp("Gauss Seidel converge en:")
itGauss

wopt=w_optimo(A,b);
disp("El w optimo es : ")
wopt




disp("EJERCICIO 4")
f_4=@(x) sin(x)+cos(1+x.^2)-1
df_4 = @(x) cos(x) - 2*x.*sin(1 + x.^2);
tol_4=1e-10;
x0=8;

m4=linspace(-10,10,1000);
figure(2)
plot(m4,f_4(m4),'r');
hold on;
plot(m4,df_4(m4),'b');

[x4,rh4,it4,t4] = NewtonRaphson(f_4,df_4,x0,1000,tol_4);
disp("El valor mas cercano a x0=8 es :")
x4
printf("%.10f", x4);

