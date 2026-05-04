clear;
f= @(x) sin(x)+cos(1+x.^2)-1;
df = @(x) cos(x) - 2.*x.*sin(1 + x.^2);
tol=1e-10;
kmax=100;

% grafico para hacer inspeccion visual
xv=linspace(0,5,50);

plot(xv,f(xv)); % tiene 3 raices, la primera esta en x=1.8 aproximadamente
grid on;

% voy a hallar la primer razi

% biseccion: le paso un intervalo que contenga a la raiz
%por ejemplo [1.5,2.3]

xmin=1.5;
xmax=2.3;

[x_b, h_b] = biseccion(f, xmin, xmax, kmax, tol);
disp('Solucion con biseccion: '), disp(x_b);
disp(['Cantidad de iteraciones: ', num2str(length(h_b) - 1)]);

% newton, le paso un valor cercano a la raiz
x0=1.8;
[x_n, h_n] = newton(f , df, x0, kmax, tol);
disp('Solucion con newton: '), disp(x_n);
disp(['Cantidad de iteraciones: ', num2str(length(h_n) - 1)]);

% secante
[x_s, h_s] = secante(f, xmin, xmax, kmax, tol);
disp('Solucion con secante: '), disp(x_s);
disp(['Cantidad de iteraciones: ', num2str(length(h_s) - 1)]);



