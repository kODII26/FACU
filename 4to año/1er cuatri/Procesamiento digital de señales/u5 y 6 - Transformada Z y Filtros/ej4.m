

% H(s) filtro pasabanda ya que numerador tiene termino con s
B1 = 12500;
A2 = 44;
A1 = 60625;
A0 = 6250000; % 625 * 10^4

% Definimos la función analógica H(s) con la estructura exacta pasabanda
H_continuo = @(s) (B1 * s) ./ (A2 * s.^2 + A1 * s + A0);

% CÁLCULO AS FRECUENCIAS DE CORTE
ganancia_max = B1 / A1;                 % Ganancia máxima central en la banda de paso
factor_corte_lineal = 10^(-3/20);       % ~0.707945
g_target_sq = (ganancia_max * factor_corte_lineal)^2; % Nivel de potencia a -3 dB exacto

% Coeficientes de la ecuación para hallar los puntos donde |H(jw)|^2 = g_target_sq
c2 = (A2^2) * g_target_sq;
c1 = (A1^2 - 2*A0*A2) * g_target_sq - B1^2;
c0 = (A0^2) * g_target_sq;

% Resolvemos las raices de la ecuación cuadrática sustituida (en términos de w^2)
w_cuadrado_raices = roots([c2, c1, c0]);

% Sacamos la raiz cuadrada para volver a rad/s y las ordenamos de menor a mayor
w_cortes = sort(sqrt(w_cuadrado_raices));

% Convertimos a Hz dividiendo por 2*pi
f_c1 = w_cortes(1) / (2 * pi);       % Frecuencia de corte inferior (~15.65 Hz)
f_c2 = w_cortes(2) / (2 * pi);       % Frecuencia de corte superior (~235.15 Hz)

% PARAMETROS DE MUESTREO
fc = f_c2;                          % Tomamos la frecuencia crítica más alta (corte superior)
fs = 4 * fc;                        % Frecuencia de muestreo (4 veces superior a fc2)
T = 1 / fs;                         % Período de muestreo

fprintf('Ganancia máxima del filtro: %.4f\n', ganancia_max);
fprintf('Frecuencia de corte inferior (fc1): %.2f Hz\n', f_c1);
fprintf('Frecuencia de corte superior (fc2): %.2f Hz\n', f_c2);
fprintf('Frecuencia de muestreo elegida (fs): %.2f Hz\n\n', fs);

% TRANSFORMACIONES CONFORMES
% Sustituimos 's' en la función continua usando las aproximaciones de los libros
H_euler = @(z) H_continuo((1 - z.^(-1)) / T);
H_bilineal = @(z) H_continuo((2/T) * (1 - z.^(-1)) ./ (1 + z.^(-1)));
% bilineal preserva estabilidad, evita aliasing

% VECTOR DE FRECUENCIAS
N = 1024;
f = linspace(0, fs/2, N);           % Vector de Hz desde 0 hasta Nyquist
w_rad = 2 * pi * f;                 % Frecuencia angular continua (rad/s)
w_dig = 2 * pi * f / fs;            % Frecuencia angular digital (rad/muestra)

% EVALUACION ESPECTRAL
H_c = H_continuo(1i * w_rad);       % Respuesta continua: s = j*w
z = exp(1i * w_dig);                % Respuesta discreta en el círculo unitario: z = e^(j*w)
H_e = H_euler(z);
H_b = H_bilineal(z);

figure('Name', 'Trabajo Práctico - Ejercicio 4');

% Gráfico de Magnitud
subplot(2, 1, 1);
plot(f, abs(H_c), 'k--', 'LineWidth', 2); hold on;
plot(f, abs(H_b), 'b', 'LineWidth', 1.5);
plot(f, abs(H_e), 'r', 'LineWidth', 1.5);
plot([fc, fc], [0, ganancia_max], 'g:', 'LineWidth', 1.5); % Línea guía en fc2
grid on; hold off;
title('Respuesta en Magnitud: Continuo vs Discretos');
xlabel('Frecuencia (Hz)'); ylabel('|H(f)|');
legend('Continuo H(s)', 'Bilineal', 'Euler', 'Frecuencia de Corte (fc2)');

% Gráfico de Fase
subplot(2, 1, 2);
plot(f, angle(H_c)*180/pi, 'k--', 'LineWidth', 2); hold on;
plot(f, angle(H_b)*180/pi, 'b', 'LineWidth', 1.5);
plot(f, angle(H_e)*180/pi, 'r', 'LineWidth', 1.5);
grid on; hold off;
title('Respuesta en Fase: Continuo vs Discretos');
xlabel('Frecuencia (Hz)'); ylabel('Fase (grados)');
legend('Continuo H(s)', 'Bilineal', 'Euler');
