addpath('../Funciones');

x=linspace(-5,6,9);
y=log(x.^2+1)-exp(x./2).*cos(pi.*x);
%necesito la derivada y evaluarla en los 2 extremos para pasarsela a la func
fp = @(x) (2*x)./(x.^2+1) ...
          - 0.5*exp(x./2).*cos(pi.*x) ...
          + pi*exp(x./2).*sin(pi.*x);

df=[fp(-5) fp(6)];

[a,b,c,d] = cubic_spline_clamped(x,y,df);
val_aprox = spline_eval(4.2, x, a, b, c, d);

val_real=log(4.2^2+1)-exp(4.2/2)*cos(pi*4.2);

errAbs = abs(val_real-val_aprox)

%item b
% busco el maximo por barrido, evaluo un muchos puntos
% y veo cual es el mas grande
xx = linspace(-5,6,100000);

yy = spline_eval(xx,x,a,b,c,d);

[maximo,idx] = max(yy);

xmax = xx(idx);
fprintf('xmax = %.5g\n',xmax);
fprintf('maximo = %.5g\n',maximo);
