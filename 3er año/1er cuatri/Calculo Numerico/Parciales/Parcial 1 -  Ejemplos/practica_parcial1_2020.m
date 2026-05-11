clc;clear all; format long;
%------------------------PREGUNTA 1----------------------;
##disp("EJERCICIO 1")
##A=[0.5 -1 0 ; -1 3 -1; 0 -1 2];
##b=[7;4;5];
##x0=b;
##tol=1e-8;
##maxit=1000;
##
##[xGS, rGS, itGS, tGS] = GaussSeidel(A, b, x0, maxit, tol);
##[xJA,rJA,itJA,t] = Jacobi(A,b,x0,maxit,tol);
##[wmin] = w_optimo(A,b)
##[xSOR, rhSOR, itSOR, tSOR] =sor(A, b, x0, maxit, tol, wmin);
##disp("Iteraciones de Gauss Seidel")
##itGS
##disp("Iteraciones de Jacobi")
##itJA
##disp("Iteraciones de sor w opt")
##itSOR

%------------------------PREGUNTA 2----------------------;
##
##f=@(x) x + exp(-10*x.^2)*cos(x);
##df = @(x) 1 - 20*x.*exp(-10*(x.^2))*sin(x) - exp(-10*(x.^2))*cos(x);
##
####figure(1)
####xx=linspace(0,30,201);
####plot(xx,f(xx),'b-')
####plot(xx,df(xx),'r-')
##
##
##[x,rh,it,t] = NewtonRaphson(f,df,0,60000,1e-6);
##%no converge

%------------------------PREGUNTA 3----------------------;

f = @(x) sin(x) + cos(1+x.^2) - 1;
df = @(x) cos(x) - (2*x.*sin(1+x.^2));

figure(1)
xx=linspace(0,10,201);
y = zeros(size(xx));

plot(xx,f(xx),'b-')
hold on;
plot(xx,df(xx),'r-')
plot(xx,y,'g-')
legend("FUNCION","DERIVADA")

x0=1;

[xNew,rh,it,t] = NewtonRaphson(f,df,x0,60000,1e-6);
disp("CONVERGE EN X:")
xNew

##pos2=0;
##raizpos=0;
##for i=1:length(xx)
##  if(f(xx(i))==0)
##    pos2=pos2+1;
##  end
##  end
##pos2
##raizpos

