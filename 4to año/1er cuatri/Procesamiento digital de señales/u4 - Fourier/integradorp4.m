# parametros base de la senal original de la parte i
fs = 1000;
t = 0:1/fs:0.999;
n_muestras = length(t);

# reconstruimos la senal original en el tiempo
s_original = 5*sin(2*pi*50*t) + 3*sin(2*pi*120*t) + 2*sin(2*pi*280*t);

# obtenemos el espectro original y el eje de frecuencias
x_k = fft(s_original);
frec = (0:n_muestras-1) * (fs/n_muestras);

# --- 1. diseno del filtro pasa-bajos ideal ---
# creamos la mascara h_k llena de unos (deja pasar todo inicialmente)
h_k = ones(1, n_muestras);

# definimos la frecuencia de corte pedida
f_corte = 200;

# aplicamos el filtro teniendo en cuenta el teorema de simetria (nyquist)
# anulamos las frecuencias entre f_corte (200 hz) y fs-f_corte (800 hz)
h_k(frec > f_corte & frec < (fs - f_corte)) = 0;

# graficamos la respuesta en frecuencia del filtro
figure(1);
subplot(3, 1, 1);
plot(frec, h_k, 'k', 'linewidth', 2);
title('respuesta en frecuencia del filtro ideal h[k]');
xlabel('frecuencia (hz)');
ylabel('amplitud h[k]');
axis([0 1000 -0.2 1.2]);
grid on;

# --- 2. aplicacion del filtro ---
# multiplicamos punto a punto el espectro original por la mascara
y_k = x_k .* h_k;

# graficamos la magnitud del espectro filtrado
subplot(3, 1, 2);
plot(frec, abs(y_k), 'b', 'linewidth', 1.5);
title('espectro de magnitud filtrado |y[k]|');
xlabel('frecuencia (hz)');
ylabel('magnitud');
grid on;

# --- 3. antitransformada y analisis temporal ---
# volvemos al dominio del tiempo usando la funcion ifft
y_n = ifft(y_k);

# descartamos la parte imaginaria residual por redondeos de la computadora
y_n = real(y_n);

# graficamos un segmento de 0 a 0.1 segundos (las primeras 100 muestras)
subplot(3, 1, 3);
plot(t(1:100), s_original(1:100), 'r--', 'linewidth', 1.5);
hold on;
plot(t(1:100), y_n(1:100), 'b', 'linewidth', 1.5);
title('senal original vs senal filtrada en el tiempo');
xlabel('tiempo (s)');
ylabel('amplitud');
legend('original (con 280hz)', 'filtrada (sin 280hz)');
grid on;

# analisis de las diferencias y el cambio en la forma de onda:
#
# 1. en el espectro filtrado (|y[k]|):
# verificamos visualmente que los picos en 280 hz y su reflejo en 720 hz
# desaparecieron completamente porque cayeron en la "zona de ceros" de h[k].
#
# 2. en el dominio temporal (original vs filtrada):
# la senal original (roja punteada) presentaba oscilaciones muy rapidas y
# "picos afilados" montados sobre la onda principal. esos picos veloces eran
# la contribucion directa de la componente de 280 hz.
#
# al remover los 280 hz mediante el filtro ideal pasa-bajos, la senal azul
# resultante (y[n]) se vuelve mucho mas suave y redondeada. esto se debe a
# que ahora unicamente esta compuesta por las sumas de las frecuencias mas
# bajas y lentas: 50 hz y 120 hz. el filtro actuo exitosamente como un
# "suavizador" de la forma de onda.
