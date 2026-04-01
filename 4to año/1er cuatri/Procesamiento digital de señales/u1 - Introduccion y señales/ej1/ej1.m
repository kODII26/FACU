

fm = 100;           % Frecuencia de muestreo en Hz
t_inicial = 0;      % Tiempo inicial en segundos
t_final = 1;        % Tiempo final en segundos

% Parámetros de la señal (2*fs <= fm, es decir fs <= 50hz)
fs = 5;             % Frecuencia de la señal en hz
phi = pi/4;         % Fase en radianes

% Generación de las señales llamando a las funciones
[y_senoidal, t] = generar_senoidal(fs, fm, phi, t_inicial, t_final);
[y_sinc, t]     = generar_sinc(fs, fm, t_inicial, t_final);
[y_cuadrada, t] = generar_cuadrada(fs, fm, phi, t_inicial, t_final);

figure; % Crea una nueva ventana para los gráficos

% 1. Gráfico de la Señal Senoidal
subplot(3, 1, 1); % Divide la ventana en 3 filas, 1 columna, y usa la posición 1
stem(t, y_senoidal, 'b', 'filled');
title('1. Señal Senoidal discreta');
xlabel('Tiempo (s)');
ylabel('Amplitud');
grid on;

% 2. Gráfico de la Señal Sinc
subplot(3, 1, 2); % Posición 2
stem(t, y_sinc, 'r', 'filled');
title('2. Señal Sinc discreta');
xlabel('Tiempo (s)');
ylabel('Amplitud');
grid on;

% 3. Gráfico de la Señal Cuadrada
subplot(3, 1, 3); % Posición 3
stem(t, y_cuadrada, 'k', 'filled');
title('3. Señal Cuadrada discreta');
xlabel('Tiempo (s)');
ylabel('Amplitud');
ylim([-1.5, 1.5]); % Ampliamos un poco el eje Y para ver bien los topes
grid on;
