addpath('../Funciones creadas');

T = 0.001;
fm = 1/T;

sen1 = generar_senoidal(10, fm, 0, 0, 1);
sen2 = generar_senoidal(20, fm, 0, 0, 1);
s = sen1 + 4*sen2;

N = length(s);
S = fft(s);

% delta F = fm/N
f = (0:N/2-1)*(fm/N);
magnitud = abs(S);

% Gráfico Base
figure(1);
% Se usa 'stem' para espectros discretos y graficamos solo la primera mitad
stem(f, magnitud(1:N/2), 'b', 'filled', 'LineWidth', 1.5);
xlabel('Frecuencia [Hz]');
ylabel('|S[k]|');
title('Espectro de magnitud - Señal Base');
xlim([0 50]); % Zoom para ver bien los picos de 10 y 20 Hz
grid on;

% -------------------------------------------------------------------------
% VERIFICACIÓN DE PARSEVAL
% -------------------------------------------------------------------------
energia_tiempo = sum(s.^2);
energia_frecuencia = (1/N) * sum(abs(S).^2);

disp('--- Relación de Parseval ---')
fprintf('Energía en el tiempo:      %.4f\n', energia_tiempo);
fprintf('Energía en la frecuencia:  %.4f\n\n', energia_frecuencia);

% -------------------------------------------------------------------------
% ÍTEM 1: Agregar nivel DC (+4)
% -------------------------------------------------------------------------
s2 = s + 4;
S2 = fft(s2);
magnitud2 = abs(S2);

% Gráfico Ítem 1
figure(2);
stem(f, magnitud2(1:N/2), 'r', 'filled', 'LineWidth', 1.5);
xlabel('Frecuencia [Hz]');
ylabel('|S[k]|');
title('Ítem 1: Espectro con componente constante (+4)');
xlim([0 50]);
grid on;
% Se observa un pico enorme en 0 Hz correspondiente a la constante.

% -------------------------------------------------------------------------
% ÍTEM 2: Frecuencia 2 = 11 Hz
% -------------------------------------------------------------------------
sen3 = generar_senoidal(11, fm, 0, 0, 1);
s3 = sen1 + 4*sen3; % Ojo: Quité el +4 extra para aislar el efecto del cambio de Hz
S3 = fft(s3);
magnitud3 = abs(S3);

% Gráfico Ítem 2
figure(3);
stem(f, magnitud3(1:N/2), 'g', 'filled', 'LineWidth', 1.5);
xlabel('Frecuencia [Hz]');
ylabel('|S[k]|');
title('Ítem 2: Frecuencias 10 Hz y 11 Hz');
xlim([0 50]);
grid on;

% -------------------------------------------------------------------------
% ÍTEM 3: Frecuencia 2 = 10.5 Hz (Agregado)
% -------------------------------------------------------------------------
sen_mod3 = generar_senoidal(10.5, fm, 0, 0, 1);
s_mod3 = sen1 + 4*sen_mod3;
S_mod3 = fft(s_mod3);
magnitud_mod3 = abs(S_mod3);

% Gráfico Ítem 3
figure(4);
stem(f, magnitud_mod3(1:N/2), 'm', 'filled', 'LineWidth', 1.5);
xlabel('Frecuencia [Hz]');
ylabel('|S[k]|');
title('Ítem 3: Frecuencias 10 Hz y 10.5 Hz (Fuga Espectral)');
xlim([0 50]);
grid on;
% Al no ser 10.5 múltiplo de la resolución (1 Hz), la energía se "desparrama".

% -------------------------------------------------------------------------
% ÍTEM 4: Aumentar ventana de tiempo a 2 segundos
% -------------------------------------------------------------------------
sen1_2s = generar_senoidal(10, fm, 0, 0, 2);
sen2_2s = generar_senoidal(10.5, fm, 0, 0, 2); % Usamos 10.5 Hz para ver la mejora

s4 = sen1_2s + 4*sen2_2s;

N4 = length(s4);
S4 = fft(s4);
magnitud4 = abs(S4);

% Nueva resolución frecuencial para 2 segundos
f4 = (0:N4/2-1)*(fm/N4);

% Gráfico Ítem 4
figure(5);
stem(f4, magnitud4(1:N4/2), 'k', 'filled', 'LineWidth', 1.5);
xlabel('Frecuencia [Hz]');
ylabel('|S[k]|');
title('Ítem 4: Ventana de 2s con f2 = 10.5 Hz');
xlim([0 50]);
grid on;
% Al duplicar el tiempo, la resolución es de 0.5 Hz. Ahora 10.5 Hz coincide
% con un bin exacto y desaparece la fuga espectral.
