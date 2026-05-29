clear; clc; close all;

% H(s) = (B1*s) / (A2*s^2 + A1*s + A0)
B1 = 12500;
A2 = 44;
A1 = 60625;
A0 = 6250000;

% ---  CÁLCULO DE PARÁMETROS ---
w0 = sqrt(A0 / A2);         % Frecuencia central de resonancia (rad/s)
f0 = w0 / (2 * pi);         % Frecuencia central (Hz)
ganancia_max = B1 / A1;     % Ganancia máxima en la banda de paso

% Puntos de corte a -3 dB
ganancia_corte = ganancia_max / sqrt(2);
g_target_sq = ganancia_corte^2;

% Ecuación bicuadrática para despejar las frecuencias de corte exactas
c2 = (A2^2) * g_target_sq;
c1 = (A1^2 - 2*A0*A2) * g_target_sq - B1^2;
c0 = (A0^2) * g_target_sq;

w_cuadrado_raices = roots([c2, c1, c0]);
w_cortes = sort(sqrt(w_cuadrado_raices));

f_c1 = w_cortes(1) / (2 * pi); % Frecuencia de corte inferior (Hz)
f_c2 = w_cortes(2) / (2 * pi); % Frecuencia de corte superior (Hz)

% --- DEFINICIÓN DE PARÁMETROS ---
fc = f_c2;          % Nos basamos en la frecuencia de corte más alta
fs = 4 * fc;        % Frecuencia de muestreo (4 veces superior)
T = 1 / fs;         % Período de muestreo

% --- OBTENCIÓN DE COEFICIENTES H(z) ---

% A) Método Bilineal
K = 2 / T;
b_bil_raw = [B1*K, 0, -B1*K];
a_bil_raw = [(A2*K^2 + A1*K + A0), (-2*A2*K^2 + 2*A0), (A2*K^2 - A1*K + A0)];
b_bil = b_bil_raw / a_bil_raw(1); % Normalización para que a0 = 1
a_bil = a_bil_raw / a_bil_raw(1);

% B) Método Euler
b_eul_raw = [B1*T, -B1*T, 0];
a_eul_raw = [(A2 + A1*T + A0*T^2), (-2*A2 - A1*T), A2];
b_eul = b_eul_raw / a_eul_raw(1); % Normalización para que a0 = 1
a_eul = a_eul_raw / a_eul_raw(1);

% --- 5. IMPRESIÓN DE RESULTADOS EN CONSOLA ---
fprintf('\n==================================================\n');
fprintf('       PARÁMETROS DEL SISTEMA CALCULADOS          \n');
fprintf('==================================================\n');
fprintf('Frecuencia central (w0) : %7.2f rad/s (%.2f Hz)\n', w0, f0);
fprintf('Ganancia máxima lineal  : %7.4f\n', ganancia_max);
fprintf('Corte inferior (fc1)    : %7.2f Hz\n', f_c1);
fprintf('Corte superior (fc2)    : %7.2f Hz\n', f_c2);
fprintf('--------------------------------------------------\n');
fprintf('Frecuencia muestreo (fs): %7.2f Hz\n', fs);
fprintf('Período de muestreo (T) : %7.7f s\n', T);
fprintf('==================================================\n');
fprintf('Coeficientes Bilineal:\n');
fprintf('b = [ %0.4f  %0.4f  %0.4f ]\n', b_bil(1), b_bil(2), b_bil(3));
fprintf('a = [ %0.4f  %0.4f  %0.4f ]\n', a_bil(1), a_bil(2), a_bil(3));
fprintf('--------------------------------------------------\n');
fprintf('Coeficientes Euler:\n');
fprintf('b = [ %0.4f  %0.4f  %0.4f ]\n', b_eul(1), b_eul(2), b_eul(3));
fprintf('a = [ %0.4f  %0.4f  %0.4f ]\n', a_eul(1), a_eul(2), a_eul(3));
fprintf('==================================================\n\n');

% ---  CÁLCULO DE LA RESPUESTA EN FRECUENCIA NATIVA ---
N = 1024;
f_vec = linspace(0, fs/2, N); % Eje Frecuencia desde 0 hasta Nyquist
w_rad = 2 * pi * f_vec;       % Eje omega continuo (rad/s)
w_dig = 2 * pi * f_vec / fs;  % Eje omega digital (rad/muestra)

% Respuesta del filtro continuo H(s)
s = 1i * w_rad;
H_continuo = (12500 * s) ./ (44 * s.^2 + 60625 * s + 6250000);

% Respuesta del filtro digital Bilineal H(z)
H_bil_num = b_bil(1) + b_bil(2)*exp(-1i*w_dig) + b_bil(3)*exp(-1i*w_dig*2);
H_bil_den = a_bil(1) + a_bil(2)*exp(-1i*w_dig) + a_bil(3)*exp(-1i*w_dig*2);
H_bilineal = H_bil_num ./ H_bil_den;

% Respuesta del filtro digital Euler H(z)
H_eul_num = b_eul(1) + b_eul(2)*exp(-1i*w_dig) + b_eul(3)*exp(-1i*w_dig*2);
H_eul_den = a_eul(1) + a_eul(2)*exp(-1i*w_dig) + a_eul(3)*exp(-1i*w_dig*2);
H_euler = H_eul_num ./ H_eul_den;

% --- 7. GRÁFICOS COMPARATIVOS ---
figure('Name', 'Comparativa de Sistemas Continuo y Discretos', 'NumberTitle', 'off');

% Subplot de Magnitud
subplot(2, 1, 1);
plot(f_vec, abs(H_continuo), 'k--', 'LineWidth', 2); hold on;
plot(f_vec, abs(H_bilineal), 'b', 'LineWidth', 1.5);
plot(f_vec, abs(H_euler), 'r', 'LineWidth', 1.5);
grid on; hold off;
title('Comparativa de Magnitud');
xlabel('Frecuencia (Hz)');
ylabel('|H(f)|');
legend('Continuo H(s)', 'Bilineal', 'Euler Invertida');

% Subplot de Fase (Convertido de radianes a grados mediante *180/pi)
subplot(2, 1, 2);
plot(f_vec, angle(H_continuo)*180/pi, 'k--', 'LineWidth', 2); hold on;
plot(f_vec, angle(H_bilineal)*180/pi, 'b', 'LineWidth', 1.5);
plot(f_vec, angle(H_euler)*180/pi, 'r', 'LineWidth', 1.5);
grid on; hold off;
title('Comparativa de Fase (Grados)');
xlabel('Frecuencia (Hz)');
ylabel('Fase (grados)');
legend('Continuo H(s)', 'Bilineal', 'Euler Invertida');
