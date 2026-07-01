K0=0.57


p= @(x) 0*x;
q= @(x) (5.*x-10)./K0;
r= @(x) -(12*cos(2.*x))./K0;
f= @(x) [p(x) q(x) r(x)];

alpha=6;
inter= [0 2];
rob= [1 0 70.1754386];
L=8000;

%item a
[xdf,u]=dif_fin_rob(f,inter,alpha,rob,L);

% hallo flujo en 0
h=xdf(2)-xdf(1);
u0= (u(2)-u(1))/h; %dif hacia adelante

%entonces phi0=-k0*u0
phi0=-K0*u0;
fprintf('flujo ext izquierdo = %.5g\n',phi0);

%item b
c=0.217;
p=2.7;
A=0.01;

Q = trapcomp(xdf,u);
E= A*c*p*Q;

fprintf('energia termica total = %.5g\n',E);

%item c
%ahora tengo robin a la izquierda y dirichlet desconocido a la derecha
% tengo que invertir la variable espacial
%nose bien com ose hace













