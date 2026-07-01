addpath('../../Funciones');

p=@(x) -11./(3.*x);
q=@(x) 1./(x.^2);
r=@(x) -log(x)./(x.^2) + 8./(3.*x.^2);
f = @(x) [p(x), q(x), r(x)];
inter=[1 4];
yc= [1 2.9736954];
L=1000;

[xdf,ydf]=dif_fin_dir(f,inter,yc,L);

%item a
index = find (xdf == 2.5);
y25=ydf(index);
fprintf(' y(2.5) = %.7f\n',y25);

%item b
h = xdf(2) - xdf(1);
%diferencia hacia adelante yp25 = (ydf(index+1) - ydf(index)) / h;
%diferencia centrada:
yp25 = (ydf(index+1) - ydf(index-1)) / (2*h);

fprintf("y'(2.5) = %.5f\n", yp25);

%item c

Q = trapcomp(xdf,ydf);
fprintf("integral de 1 a 4 = %.5f\n", Q);
