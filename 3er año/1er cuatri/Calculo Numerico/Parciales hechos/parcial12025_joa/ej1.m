addpath('../Funciones');

f= @(x) log(x.^2+1)-exp(x./2).*cos(pi.*x)-1.106;

% grafico para item a
%xv=linspace(-6,6,200);
%hold on;
%grid on;
%plot(xv,f(xv));
% veo 7 raices

% item b
tol=1e-7;
kmax=100;
xmin=-1;
xmax=0;

[x, h] = biseccion(f, xmin, xmax, kmax, tol);
fprintf('x = %.7f\n', x);
disp('Iteraciones: '), disp(length(h)-1);

% item c
tol=1e-10;
df = @(x) (2*x)./(x.^2 + 1) - exp(x./2).*(0.5*cos(pi*x) - pi*sin(pi*x));

x0=3;
[x_1, h_1] = newton(f, df, x0, kmax, tol);
fprintf('x1 = %.10f\n', x_1);

x0=3.05;
[x_2, h_2] = newton(f, df, x0, kmax, tol);
fprintf('x2 = %.10f\n', x_2);

x0=3.1;
[x_3, h_3] = newton(f, df, x0, kmax, tol);
fprintf('x3 = %.10f\n', x_3);

% item d
g = @(x) log(x.^2+1)-exp(x/2).*cos(pi*x)-1.106 -x ;

[x_p, h_p] = biseccion(g, 0.5, 1.5, 100, 1e-7);
disp(x_p);
















