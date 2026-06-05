clear; clc; close all;
pkg load signal;

%coef de x (numerador)
b = [1, 0.5];
%coef de y (denominador)
a = [1, -0.8, 0.12];

fm = 1000;

% parte 1
[ceros, polos, ganancia] = tf2zp(b, a);

figure(1);
zplane(b, a);
grid on;
title('Diagrama de Polos y Ceros en el Plano Z');
xlabel('Parte Real');
ylabel('Parte Imaginaria');
disp('--- ANALISIS EN DOMINIO Z ---');
fprintf('Ceros en: %s\n', num2str(ceros.'));
fprintf('Polos en: %s\n', num2str(polos.'));
if all(abs(polos) < 1)
    disp('El sistema es ESTABLE (todos los polos estan dentro del circulo unitario).');
else
    disp('El sistema es INESTABLE.');
end

% parte 2
N = 512;             % Puntos de la grilla de frecuencias

[H, w] = freqz(b, a, N);

f_norm = w / pi;          % Frecuencia normalizada (0 a 1)
f_hz = (w / (2*pi)) * fm; % Frecuencia en Hz
magnitud = abs(H);
fase_grados = angle(H) * 180 / pi; % Fase en grados

% graficos
figure(1);

subplot(2,2,1);
plot(f_norm, magnitud, 'b', 'linewidth', 2); grid on;
title('Magnitud vs Frec. Normalizada');
xlabel('Frecuencia (\times \pi rad/muestra)'); ylabel('|H|');

subplot(2,2,3);
plot(f_norm, angle(H), 'r', 'linewidth', 2); grid on;
title('Fase vs Frec. Normalizada');
xlabel('Frecuencia (\times \pi rad/muestra)'); ylabel('Fase (rad)');

subplot(2,2,2);
plot(f_hz, magnitud, 'b', 'linewidth', 2); grid on;
title(['Magnitud vs Frecuencia (fm = ', num2str(fm), ' Hz)']);
xlabel('Frecuencia (Hz)'); ylabel('|H(f)|');

subplot(2,2,4);
plot(f_hz, fase_grados, 'r', 'linewidth', 2); grid on;
title('Fase vs Frecuencia (Hz)');
xlabel('Frecuencia (Hz)'); ylabel('Fase (grados)');


% resp al impulso -> impz
% guardamos los datos para dsp analizar estabilidad
[h, n_vec] = impz(b, a);

% graficos
figure(2);
impz(b, a);
grid on;
title('Respuesta al Impulso h[n] calculada por impz');
xlabel('Muestras (n)'); ylabel('Amplitud');

suma_absoluta = sum(abs(h));
disp('VERIFICACION DE ESTABILIDAD (PARTE II)');
fprintf('Muestras evaluadas automaticamente por impz: %d\n', length(h));
fprintf('Suma absoluta de las muestras: %f\n', suma_absoluta);
