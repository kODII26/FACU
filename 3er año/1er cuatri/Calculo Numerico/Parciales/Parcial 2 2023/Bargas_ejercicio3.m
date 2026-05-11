clc;
clear all;
disp("=============================================================")
disp("------------------------pregunta5 --------------------------")
format long;
f=@(x) 2+cos(x)-sin(3*x);

df=@(x) -sin(x)-3*cos(3*x);
F = @(x) 2*pi*f(x).*sqrt(1+df(x).^2);
%inter=[0,3];
a=0;
b=3;
n=3;
L=30;
Q=cuad_gauss_c(F,a,b,L,n);
Q
%[S]= SimpsonCompuesto(F,a,b,L);
%S
%q = quad(F,a,b);
%q

%para ver la cantidad de cifras exactas aumentamos la L
%Q=cuad_gauss_c(F,a,b,40,n);
%Q
%Q=cuad_gauss_c(F,a,b,80,n);
%Q
%Q=cuad_gauss_c(F,a,b,160,n);
%Q
%Q=cuad_gauss_c(F,a,b,320,n);
%Q

