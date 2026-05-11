addpath('Funciones');

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
