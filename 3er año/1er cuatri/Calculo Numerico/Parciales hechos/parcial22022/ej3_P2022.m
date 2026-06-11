addpath('Funciones');
format long

f=@(x) 2.5 + x.*cos(2.*x);
df= @(x) cos(2*x)-2.*x.*sin(2*x);
n=3;
L=20;

S=@(x) 2*pi.*f(x).*sqrt(1+df(x).^2);

Q=cuad_gauss_c(S,0,3,L,n)

Qex = integral(S,0,3)


