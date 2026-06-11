addpath('Funciones');
format long

f=@(x) 2 + cos(pi.*x);
df= @(x) pi*sin(pi.*x);
n=3;
L=40;9

S=@(x) 2*pi.*f(x).*sqrt(1+df(x).^2);

Q=cuad_gauss_c(S,0,2,L,n)

Qex = integral(S,0,2)


