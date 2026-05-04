% item b

x0=1;
kmax=100;
tol=1e-4;

g1=@(x) (3+x-2.*x.^2).^0.25;

[x1, h1] = puntofijo(g1, x0, kmax, tol);
disp('Solucion con g1: '), disp(x1);
disp(['Cantidad de iteraciones: ', num2str(length(h1) - 1)]);

g2=@(x) ((x+3-x.^4)./2).^0.5;

[x2, h2] = puntofijo(g2, x0, kmax, tol);
disp('Solucion con g2: '), disp(x2);
disp(['Cantidad de iteraciones: ', num2str(length(h2) - 1)]);

g3=@(x) ((x+3)./(x.^2+2)).^0.5;

[x3, h3] = puntofijo(g3, x0, kmax, tol);
disp('Solucion con g3: '), disp(x3);
disp(['Cantidad de iteraciones: ', num2str(length(h3) - 1)]);

g4=@(x) (3.*x.^4+2.*x.^2+3)./(4.*x.^3+4.*x-1);

[x4, h4] = puntofijo(g4, x0, kmax, tol);
disp('Solucion con g4: '), disp(x4);
disp(['Cantidad de iteraciones: ', num2str(length(h4) - 1)]);



% item c








