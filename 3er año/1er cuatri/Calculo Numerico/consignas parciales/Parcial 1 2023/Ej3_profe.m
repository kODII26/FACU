clear all; close all; clc;

format long
n = 39;
U = generarMatrizU_ciclos(n);
b = generarVectorCargas(n);

x0 = zeros(n,1);
[x,r,it] = GaussSeidel(U,b,x0,10000,1e-6);

disp (it)
%%%%%

disp(x(20))
