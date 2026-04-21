A_1= [3 1 1; 1 3 -1; 3 1 -5];
b_1= [5 3 -1]';

% function [x,it,r_h]=gauss_seidel(A,b,x0,maxit,tol)
x0=zeros(length(b_1),1); maxit=1000; tol=1e-8;


[x_1,it_1,r_h_1]=gauss_seidel(A_1,b_1,x0,maxit,tol);
x_1


A_2= [3 1 1; 3 1 -5; 1 3 -1];
b_2= [5 -1 3]';

% function [x,it,r_h]=gauss_seidel(A,b,x0,maxit,tol)
x0=zeros(length(b_2),1); maxit=1000; tol=1e-8;


[x_2,it_2,r_h_2]=gauss_seidel(A_2,b_2,x0,maxit,tol);
x_2
% Esto no converge, la justificacion es que ademas de que al intercambiar
% Las filas te queda una matriz que no es diagonal dominante,
% Si armas la matriz de transicion y le calculas el radio espectral
% vas a ver que es mayor que 1 por lo tanto ahi si podes determinar
% que no converge

% Gauss directo:
addpath('../Funciones');

[x_3]=gauss1(A_1,b_1);
x_3

[x_4]=gauss1(A_2,b_2);
x_4

%Este no da resultado ya que el pivote en la 2da fila queda cero
% y trata de dividir por cero, se puede resolver con pivoteo parcial







