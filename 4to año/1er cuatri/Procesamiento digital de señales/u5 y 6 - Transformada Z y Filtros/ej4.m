

% H(s) filtro pasabanda ya que numerador tiene termino con s
B1 = 12500;
A2 = 44;
A1 = 60625;
A0 = 6250000; % 625 * 10^4

% definimos H(s)
H_continuo = @(s) (B1 * s) ./ (A2 * s.^2 + A1 * s + A0);

% frec de corte
ganancia_max = B1 / A1;
factor_corte_lineal = 10^(-3/20);% aprox 0.707945
g_target_sq = (ganancia_max * factor_corte_lineal)^2; % nivel de potencia a -3 dB

% coef de la ecuacion
c2 = (A2^2) * g_target_sq;
c1 = (A1^2 - 2*A0*A2) * g_target_sq - B1^2;
c0 = (A0^2) * g_target_sq;

% raices de la ec cuadratica
w_cuadrado_raices = roots([c2, c1, c0]);

% sacamos la raiz cuadrada para volver a rad/s y las ordenamos de menor a mayor
w_cortes = sort(sqrt(w_cuadrado_raices));

% convertimos a Hz
f_c1 = w_cortes(1) / (2 * pi);% c orte inferior
f_c2 = w_cortes(2) / (2 * pi);%corte superior

%parametros de muestreo
fc = f_c2; % tomamos corte superior
fm = 4 * fc;
T = 1 / fm;

fprintf('Ganancia máxima del filtro: %.4f\n', ganancia_max);
fprintf('Frecuencia de corte inferior (fc1): %.2f Hz\n', f_c1);
fprintf('Frecuencia de corte superior (fc2): %.2f Hz\n', f_c2);
fprintf('Frecuencia de muestreo elegida (fm): %.2f Hz\n\n', fm);

% sustituimos 's' en la función continua usando las aproximaciones del apunte
H_euler = @(z) H_continuo((1 - z.^(-1)) / T);
H_bilineal = @(z) H_continuo((2/T) * (1 - z.^(-1)) ./ (1 + z.^(-1)));
% bilineal preserva estabilidad, evita aliasing

%vector de frec
N = 1024;
f = linspace(0, fm/2, N);
w_rad = 2 * pi * f; % frec angular cont
w_dig = 2 * pi * f / fm; % frec angular digital

% evaluacion espectral
H_c = H_continuo(1i * w_rad);
z = exp(1i * w_dig);
H_e = H_euler(z);
H_b = H_bilineal(z);

figure('Name', 'Trabajo Práctico - Ejercicio 4');

%graficos
subplot(2, 1, 1);
plot(f, abs(H_c), 'k--', 'LineWidth', 2); hold on;
plot(f, abs(H_b), 'b', 'LineWidth', 1.5);
plot(f, abs(H_e), 'r', 'LineWidth', 1.5);
plot([fc, fc], [0, ganancia_max], 'g:', 'LineWidth', 1.5);
grid on; hold off;
title('Respuesta en Magnitud: Continuo vs Discretos');
xlabel('Frecuencia (Hz)'); ylabel('|H(f)|');
legend('Continuo H(s)', 'Bilineal', 'Euler', 'Frecuencia de Corte (fc2)');

subplot(2, 1, 2);
plot(f, angle(H_c)*180/pi, 'k--', 'LineWidth', 2); hold on;
plot(f, angle(H_b)*180/pi, 'b', 'LineWidth', 1.5);
plot(f, angle(H_e)*180/pi, 'r', 'LineWidth', 1.5);
grid on; hold off;
title('Respuesta en Fase: Continuo vs Discretos');
xlabel('Frecuencia (Hz)'); ylabel('Fase (grados)');
legend('Continuo H(s)', 'Bilineal', 'Euler');
