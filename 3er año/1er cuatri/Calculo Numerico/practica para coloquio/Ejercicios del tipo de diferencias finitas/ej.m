addpath('../Funciones');

Lbarra=5;
K0=0.9;


p=@(x) 0*x;
q=@(x) (0.5.*x+0.5)./K0;
r=@(x) -(25.*x-5.*x.^2)./K0;

f=@(x) [p(x) q(x) r(x)];

inter=[0 5];
ycd=6;
rob=[-0.9 -15 -60];
L=1000;


[xdf,udf]=dif_fin_rob(f,inter,ycd,rob,L);

%item a
index = find(xdf==2.5);
u25 = udf(index);
fprintf("u(2.5) = %.4f\n",u25);

%item  b
%tengo q aproximar u' en 0
h=xdf(2)-xdf(1);
u0= (udf(2)-udf(1))/h;
phi0= -K0*u0;
fprintf("flujo en ext izquierdo = %.6f\n",phi0);


