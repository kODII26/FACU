# parametros iniciales del sistema
fs = 1000;
t = 0:1/fs:0.999;
n_muestras = length(t);

# definicion de las frecuencias y amplitudes
f1 = 50;
f2 = 120;
f3 = 280;

# generacion de las senales individuales por separado
# nota: uso cos() para x2 tal como lo pide estrictamente la consigna
x1 = 5 * sin(2 * pi * f1 * t);
x2 = 3 * cos(2 * pi * f2 * t);
x3 = 2 * sin(2 * pi * f3 * t);

# senal compuesta (la suma en el tiempo)
s_compuesta = x1 + x2 + x3;

# --- verificacion de la linealidad ---
# calculo de la tdf para cada senal individual
tdf_x1 = fft(x1);
tdf_x2 = fft(x2);
tdf_x3 = fft(x3);

# sumo los espectros individuales
suma_de_tdfs = tdf_x1 + tdf_x2 + tdf_x3;

# calculo la tdf de la senal que ya estaba sumada en el tiempo
tdf_total = fft(s_compuesta);

# generacion del eje de frecuencias para graficar
df = fs / n_muestras;
frec = (0:n_muestras-1) * df;

# grafica para comprobar visualmente que ambas curvas se superponen perfecto
figure(1);
plot(frec, abs(tdf_total), 'b', 'linewidth', 3);
hold on;
plot(frec, abs(suma_de_tdfs), 'r--', 'linewidth', 2);
title('verificacion de linealidad: tdf total vs suma de tdfs');
xlabel('frecuencia (hz)');
ylabel('magnitud');
legend('tdf de s[n] conjunta', 'suma de tdf1, tdf2 y tdf3');
grid on;
axis(); # zoom a la zona de interes
pause(10);
# --- verificacion del teorema de parseval ---
# 1. energia total en el dominio del tiempo (suma de los cuadrados)
energia_tiempo = sum(s_compuesta.^2);

# 2. energia total en el dominio de la frecuencia
# (suma de las magnitudes al cuadrado, dividida por el total de muestras n)
energia_frecuencia = sum(abs(tdf_total).^2) / n_muestras;

# mostramos los resultados en la consola
fprintf('\n--- verificacion teorema de parseval ---\n');
fprintf('energia en el tiempo:     %.4f\n', energia_tiempo);
fprintf('energia en la frecuencia: %.4f\n', energia_frecuencia);

# si los valores impresos son identicos, la energia se conservo exitosamente.
