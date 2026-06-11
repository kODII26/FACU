addpath('Funciones');
x=[0 0.2 0.4 0.6 0.8 1 1.2 1.4];
y=[0.0653 0.066 0.0657 0.0651 0.0635 0.0611 0.058 0.0544];

z=1./y;

A=[ ones(length(x),1) exp(x') exp(-x')];

w = A\z';

a=w(1);
b=w(2);
c=w(3);

printf("a = %.4f\nb = %.4f\nc = %.4f\n", a, b, c);

%item b


f_intersect = @(x) 1 ./ (a + b * exp(x) + c * exp(-x)) - x ./ 20;

xx=linspace(0,2,1000);

plot(xx,f_intersect(xx))
grid on %veo que el cruce esta entre 1.1 y 1.2

[x_inter, h] = secante(f_intersect, 0, 1.2, 10000, 1e-8);
printf("x (interseccion) = %.7f\n", x_inter);
% verificar presicion con metodo de octave:
corte_octave = fzero(f_intersect,0.5);
disp("corte fzero octave");
disp(corte_octave);

%item c
f_curva = @(x) 1 ./ (a + b*exp(x) + c*exp(-x));
g_linea = @(x) x / 20;
x_vals = linspace(0, x_inter, 1000);
fx_vals = f_curva(x_vals) - g_linea(x_vals);
area = trapcomp(x_vals, fx_vals);
printf("area = %.7f\n", area);

