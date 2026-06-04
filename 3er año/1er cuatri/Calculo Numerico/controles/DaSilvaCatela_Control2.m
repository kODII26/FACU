addpath('Funciones');

v=1.004e-6;
tol = 1e-6;
kmax = 100;
Re = 4e5;
er = 0.00060;

g = @(f) (1 ./ (-2 .* log10(er/3.7 + 2.51 ./ (Re .* sqrt(f))))).^2;

%xv=linspace(0,1,100);
%plot(xv,f(xv));

x0 = 0.02;

[f, h] = puntofijo(g, x0, kmax, tol);

disp('El factor de friccion es : '), disp(f);

% item b



fricc=0.018;
vel=5;
d= @(D) (1 ./ (-2 .* log10(er/3.7 + 2.51 ./ ((vel.*D)./v .* sqrt(fricc))))).^2-fricc;
xv=linspace(0,0.1,100);
plot(xv,d(xv));

x0 = 0.05;
x1 = 0.1;

[x_d,h] = secante(d,x0,x1,kmax,tol);

fprintf('Diametro D = %.5f m\n',x_d);



