# 1. acortar la senal a 40 ms
# definimos los parametros iniciales
fs = 1000;
t0 = 0.04; # 40 milisegundos
t_corto = 0:1/fs:(t0 - 1/fs);
n_corto = length(t_corto); # esto nos da exactamente n = 40 muestras

# calculamos la nueva resolucion frecuencial
# df = fs / n = 1000 / 40 = 25 hz
df_corta = fs / n_corto;

# generamos la senal original pero solo para estos 40 ms
s_corta = 5*sin(2*pi*50*t_corto) + 3*sin(2*pi*120*t_corto) + 2*sin(2*pi*280*t_corto);

# aplicamos la transformada (tdf)
tdf_corta = fft(s_corta);
mag_corta = abs(tdf_corta);
frec_corta = (0:n_corto-1) * df_corta;

# ¿puedo distinguir los dos picos de 50 hz y 120 hz?
# respuesta: si, se pueden distinguir porque la distancia fisica
# entre ellos es de 70 hz, lo cual es mucho mayor a nuestra resolucion
# minima de 25 hz.
# ¿por que se ven raros? porque 50 hz es multiplo exacto de 25 hz (cae en el indice 2),
# pero 120 hz no es multiplo de 25. por lo tanto, el pico de 120 hz sufre
# fuga espectral y se deforma, perdiendose entre los indices.

# 2. relleno con ceros (zero-padding)
# extendemos la longitud de la senal hasta 5n muestras
n_extendido = 5 * n_corto; # 5 * 40 = 200 muestras totales

# rellenamos la senal original agregando ceros al final
# usamos la sintaxis de concatenacion de vectores
s_extendida = [s_corta, zeros(1, n_extendido - n_corto)];

# calculamos la nueva transformada de la senal rellena
tdf_extendida = fft(s_extendida);
mag_extendida = abs(tdf_extendida);

# calculamos el nuevo paso frecuencial de visualizacion
# df = 1000 / 200 = 5 hz
df_extendida = fs / n_extendido;
frec_extendida = (0:n_extendido-1) * df_extendida;

# 3. graficacion superpuesta
figure(1);
# usamos plot con marcadores circulares para ver los pocos puntos de la senal corta
plot(frec_corta, mag_corta, 'b-o', 'linewidth', 1.5);
hold on;
# usamos una linea roja continua para ver la interpolacion del zero-padding
plot(frec_extendida, mag_extendida, 'r-', 'linewidth', 1.5);

title('espectro con 40ms vs zero-padding');
xlabel('frecuencia (hz)');
ylabel('magnitud');
legend('espectro original (n=40)', 'espectro interpolado (n=200)');
axis(); # hacemos zoom para ver mejor los picos
grid on;
pause(10);
# ¿mejora la capacidad de distinguir las dos frecuencias con el relleno?
# respuesta: el relleno con ceros mejora la "visualizacion" del espectro.
# al agregar ceros pasamos a tener un punto cada 5 hz en lugar de cada 25 hz.
# esto nos permite "dibujar" y ver donde esta exactamente la punta de la campana
# que se habia fugado en los 120 hz.
#
# diferencia teorica vital:
# no mejoramos la "resolucion espectral" real. mejorar la resolucion
# real implica hacer mas angosto el lobulo para separar dos señales muy pegadas,
# y eso solo se logra tomando muestras reales por mas tiempo (aumentando t0).
# mejorar la visualizacion (interpolacion por zero-padding) no hace
# a los lobulos mas angostos, solo dibuja sus curvas con mas definicion.
