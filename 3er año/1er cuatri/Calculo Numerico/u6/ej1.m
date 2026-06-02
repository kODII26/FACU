clear;
clc;
close all;

f = @(x) exp(x)-2*x.^2+3*x-1;

x0 = 0;

% Derivada exacta
df_exacta = 4; %evaluada en x0

% Barrido de h
h = logspace(-11,-1,200);

error_abs = zeros(size(h));

for i=1:length(h)

    % Formula progresiva de 2 puntos
    df_aprox = (f(x0+h(i))-f(x0))/h(i);

    error_abs(i) = abs(df_exacta-df_aprox);

end

figure
loglog(h,error_abs,'LineWidth',2)
grid on
xlabel('h')
ylabel('Error absoluto')
title('Error de la formula progresiva de 2 puntos')

% Inciso b
h_b = 0.1;

df_aprox_b = (f(x0+h_b)-f(x0))/h_b;

error_real = abs(df_exacta-df_aprox_b);

f2 = @(x) exp(x)-4;

norma_f2 = max(abs(f2([0 h_b])));

cota = norma_f2*h_b/2;

fprintf('Derivada exacta     = %.10f\n',df_exacta);
fprintf('Derivada aproximada = %.10f\n',df_aprox_b);
fprintf('Error real          = %.10f\n',error_real);
fprintf('Cota teorica        = %.10f\n',cota);
