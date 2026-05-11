clc
clear


disp("EJERCICIO 1")
A=[0.5 -1 0 ; -1 3 -1; 0 -1 2];
b=[7;4;5];
x0_1=[7;4;5];
maxit_1 = 1000;
tol_1= 1e-8;

[xGauss, rGauss, itGauss, tGauss] = GaussSeidel(A, b, x0_1, maxit_1, tol_1);
rEspectralGaussSeidel=RadioEspectral(A,'gs',0)
disp("Gauss Seidel converge en:")
itGauss

wopt=w_optimo(A,b);
disp("El w optimo es : ")
wopt
[xSOR, rhSOR, itSOR, tSOR] =sor(A, b, x0_1, maxit_1, tol_1, wopt);
disp("El sor converge en ")
itSOR
rEspectralSOR=RadioEspectral(A,'aa',wopt)



[xJac,rJac,itJacobi,tJacobi] = Jacobi(A,b,x0_1,maxit_1,tol_1);
rEspectralJacobi=RadioEspectral(A,'ja',0);
disp("Jacobi converge ya que su radio espectral < 1")


%el w optimo esta entre 1 y 1.5
%GaussSeidel converge en 112 iteraciones y Jacobi en 59
%Jacobi y GaussSeidel convergen
%Sor converge en 12 iteraciones con el w optimo

disp("EJERCICIO 2")

f_2=@(x) x + (exp(-10*(x^2)) * cos(x))
df_2 = @(x) 1 - 20*x*exp(-10*(x^2))*sin(x) - exp(-10*(x^2))*cos(x);

tol_2=1e-6;
x0_2=0;
maxit_2=1000;

[xNew,rhNew,itNew,tNew] = NewtonRaphson(f_2,df_2,x0_2,maxit_2,tol_2)

%No converge


disp("EJERCICIO 4")
f_4=@(x) sin(x) + cos(1+x.^2) - 1
df_4 = @(x) cos(x) - 2*x*sin(1+x.^2);
x0_4=1;
kmax_4=1000;
tol_4=1e-8;

m=linspace(0,8,100000);
plot(m,f_4(m));
[xNew,rhNew,itNew,tNew] = NewtonRaphson(f_4,df_4,x0_4,kmax_4,tol_4)

%si nos fijamos la x con el metodo newtonRapshon da 6.935322725378638
%y en la grafica es la quinta raiz positiva

