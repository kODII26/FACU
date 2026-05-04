kmax=100;
tol=1e-4;
y=@(x) x.^2;
xv=linspace(0,2,100);
plot(x,y(xv));
x0=1;

% distancia al punto (1,0)
% (x-a)^2+(x-b)^2
% (x-1)^2+(x-0)^2
% x^4+x^2-2x+1
% para minimizar esta funcion hay q derivarla e igualarla a cero
f=@(x) 4.*x.^3+2.*x-2;
df= @(x) 12.*x.^2+2;

[x, h] = newton(f, df, x0, kmax, tol)
