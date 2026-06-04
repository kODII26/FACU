addpath('../Funciones');

T = @(t) exp(-0.15.*t) .* (cos(pi.*t) + sin(pi.*t));
tv=linspace(9,11,200);
hold on
grid on
yline(0.3)
plot(tv,T(tv));
% veo 11 cruces al 0.3

% item b
f_b = @(t) T(t) - 0.3;
tv = linspace(7.5, 8.1, 200);
figure
hold on
grid on
plot(tv,f_b(tv));


a = 7;
b = 8;
tol_b = 1e-7;
kmax = 100;
[t_raiz_b, h_b] = biseccion(f_b, a, b, kmax, tol_b);
iter_b = length(h_b) - 1;

fprintf('Iteraciones: %d\n', iter_b);
fprintf('Raíz hallada (tiempo): %.7f\n\n', t_raiz_b);

% item c
% el maximo se encuentra derivando e igualando a cero
dT = @(t) exp(-0.15.*t) .* ( (pi - 0.15).*cos(pi.*t) - (pi + 0.15).*sin(pi.*t) );
tol_c = 1e-7;

[t_M, h_c] = biseccion(dT, 8, 8.5, kmax, tol_c);
T_max = T(t_M);

fprintf('Tiempo del pico máximo: %.7f\n', t_M);
fprintf('Temperatura máxima (TM): %.7f\n\n', T_max);


% item d
% T(t) = tmax -> T(t) - tmax = 0
f_d = @(t) T(t) - T_max;
tol_d = 1e-10;

[t0, h_d0] = newton(f_d, dT, 6.15, kmax, tol_d);
[t1, h_d1] = newton(f_d, dT, 6.25, kmax, tol_d);
[t2, h_d2] = newton(f_d, dT, 6.35, kmax, tol_d);

fprintf('para t0 se obtuvo t = %.10f\n ', t0);
fprintf('para t1 se obtuvo t = %.10f\n ', t1);
fprintf('para t2 se obtuvo t = %.10f\n ', t2);

%las convergencias son todas cuadraticas ya que se calcularon con newton









