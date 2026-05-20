# definimos los parametros del sistema
fs = 1000;
n_muestras = 1000;
t = (0:n_muestras-1)/fs;
# creamos tres vectores llenos de ceros para nuestras ventanas
p_angosto = zeros(1, n_muestras);
p_medio = zeros(1, n_muestras);
p_ancho = zeros(1, n_muestras);
# llenamos con unos la region central para concentrar la energia temporal

# pulso muy concentrado en el tiempo de 10 muestras
p_angosto(495:505) = 1;
# pulso de concentracion media de 100 muestras
p_medio(450:550) = 1;
# pulso muy disperso en el tiempo de 800 muestras
p_ancho(100:900) = 1;

# calculamos las transformadas discretas de fourier de cada ventana
# usamos abs para obtener la magnitud del espectro
# usamos fftshift para correr la frecuencia 0 hz exactamente al centro del eje
f_angosto = fftshift(abs(fft(p_angosto)));
f_medio = fftshift(abs(fft(p_medio)));
f_ancho = fftshift(abs(fft(p_ancho)));

# definimos el eje x de frecuencias simetrico para poder visualizarlo bien
frec = (-n_muestras/2 : n_muestras/2 - 1) * (fs / n_muestras);

# preparamos una figura con seis graficos enfrentados
figure(1);

# graficos de los pulsos en el dominio del tiempo
subplot(3, 2, 1);
plot(t, p_angosto, 'b', 'LineWidth', 1.5);
title('pulso muy concentrado (corto)');

subplot(3, 2, 3);
plot(t, p_medio, 'g', 'LineWidth', 1.5);
title('pulso de concentracion media');

subplot(3, 2, 5);
plot(t, p_ancho, 'r', 'LineWidth', 1.5);
title('pulso disperso (largo)');

# graficos de los espectros en el dominio de la frecuencia
subplot(3, 2, 2);
plot(frec, f_angosto, 'b', 'LineWidth', 1.5);
title('espectro muy disperso (ancho)');
axis([-100 100 0 15]);

subplot(3, 2, 4);
plot(frec, f_medio, 'g', 'LineWidth', 1.5);
title('espectro de dispersion media');
axis([-100 100 0 110]);

subplot(3, 2, 6);
plot(frec, f_ancho, 'r', 'LineWidth', 1.5);
title('espectro muy concentrado (angosto)');
axis([-100 100 0 850]);
pause(15);
