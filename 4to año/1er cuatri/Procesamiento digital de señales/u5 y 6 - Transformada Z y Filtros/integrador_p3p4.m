%coef del sistema discreto obtenido por Euler
b_euler = 0.090909;
a_euler = [1, -0.909091];

T = 0.1;
fs = 1 / T;
f_nyq = fs / 2;

%grilla de frecuencias en H
N = 1000;
f_hz = linspace(0, f_nyq, N);

%resp en frec del sistema continuo Ha(s) = 1 / (s + 1)
s = 1i * 2 * pi * f_hz;
H_continuo = 1 ./ (s + 1);

% resp en frec del sistema discreto
w = 2 * pi * f_hz / fs;
k_a = (0:length(a_euler)-1).';

%evaluo denominador discreto: 1 - 0.9091 * exp(-1i * w)
H_den_discreto = a_euler * exp(-1i * k_a * w);
H_discreto = b_euler ./ H_den_discreto;

H_euler = H_discreto;

%graficos
figure(1);

subplot(2,1,1);
plot(f_hz, abs(H_continuo), 'r-', 'LineWidth', 2, 'DisplayName', 'Continuo Ha(s)');
hold on;
plot(f_hz, abs(H_discreto), 'b--', 'LineWidth', 2, 'DisplayName', 'Discreto H(z) [Euler]');
grid on;
title('Comparación de Respuesta en Magnitud (Parte III)');
xlabel('Frecuencia (Hz)'); ylabel('|H(f)|');
legend('show');

subplot(2,1,2);
plot(f_hz, angle(H_continuo) * 180 / pi, 'r-', 'LineWidth', 2, 'DisplayName', 'Continuo Ha(s)');
hold on;
plot(f_hz, angle(H_discreto) * 180 / pi, 'b--', 'LineWidth', 2, 'DisplayName', 'Discreto H(z) [Euler]');
grid on;
title('Comparación de Respuesta en Fase (Parte III)');
xlabel('Frecuencia (Hz)'); ylabel('Fase (grados)');
legend('show');


% parte 4
% Bilineal
b_bilin = [0.047619, 0.047619];
a_bilin = [1, -0.904762];

% espectro cont
H_continuo = 1 ./ (s + 1);

% espectro disc
k_bbilin = (0:length(b_bilin)-1).';
k_abilin = (0:length(a_bilin)-1).';

H_num_bilin = b_bilin * exp(-1i * k_bbilin * w);
H_den_bilin = a_bilin * exp(-1i * k_abilin * w);
H_bilin = H_num_bilin ./ H_den_bilin;

% graficos
figure(2);

subplot(2,1,1);
cla;
plot(f_hz, abs(H_continuo), 'r-', 'LineWidth', 2, 'DisplayName', 'Continuo Ha(s)');
hold on;
plot(f_hz, abs(H_euler), 'b--', 'LineWidth', 2, 'DisplayName', 'Discreto (Euler)');
plot(f_hz, abs(H_bilin), 'g-.', 'LineWidth', 2, 'DisplayName', 'Discreto (Bilineal)');
grid on;
title('Comparación de Respuesta en Magnitud (Tres Sistemas - Parte IV)');
xlabel('Frecuencia (Hz)'); ylabel('|H(f)|');
legend('show');

subplot(2,1,2);
cla;
plot(f_hz, angle(H_continuo) * 180 / pi, 'r-', 'LineWidth', 2, 'DisplayName', 'Continuo Ha(s)');
hold on;
plot(f_hz, angle(H_euler) * 180 / pi, 'b--', 'LineWidth', 2, 'DisplayName', 'Discreto (Euler)');
plot(f_hz, angle(H_bilin) * 180 / pi, 'g-.', 'LineWidth', 2, 'DisplayName', 'Discreto (Bilineal)');
grid on;
title('Comparación de Respuesta en Fase (Tres Sistemas - Parte IV)');
xlabel('Frecuencia (Hz)'); ylabel('Fase (grados)');
legend('show');
