# parametros iniciales del problema
fm = 360;
# cargamos el archivo de texto con el electrocardiograma
x = load('necg.txt');
# calculamos la cantidad de muestras totales
n_muestras = length(x);
# creamos el vector de tiempo real en segundos para poder graficar
t = (0:n_muestras-1) / fm;

# 1. pasamos la senal al dominio de la frecuencia usando la tdf
x_k = fft(x);
# 2. armamos el vector universal de frecuencias en hz usando la formula teorica
frec = (0:n_muestras-1) * (fm / n_muestras);

# 3. creacion de la mascara del filtro ideal (h_k)
# primero, llenamos un vector de unos del mismo tamano que el ecg.
# los unos significan que, por defecto, dejamos pasar todas las frecuencias.
h_k = ones(n_muestras, 1);

# 4. aplicamos el concepto de simetria y bloqueamos el ruido.
# el enunciado pide eliminar la banda de ruido de 40 a 180 hz.
# por la simetria conjugada, el ruido tambien se refleja de 180 a 320 hz (360 - 40).
# ponemos un 0 absoluto en todos los indices que caigan en ese rango
h_k(frec >= 40 & frec <= 320) = 0;
# 5. aplicamos el filtro multiplicando espectro contra mascara
# usamos .* para forzar que sea elemento a elemento
y_k = x_k .* h_k;
# 6. volvemos al dominio del tiempo usando la tdf inversa
y = ifft(y_k);
# como la computadora deja un pequeñisimo residuo imaginario por redondeos,
# usamos la funcion real() para forzar a que sea una senal fIsica pura.
y = real(y);

# 7. graficamos para observar la magia del filtro
figure(1);

subplot(2, 1, 1);
plot(t, x, 'r');
title('ecg original (contaminado con ruido de alta frecuencia)');
xlabel('tiempo (s)');
ylabel('amplitud');

subplot(2, 1, 2);
plot(t, y, 'b');
title('ecg filtrado (ruido eliminado mediante tdf)');
xlabel('tiempo (s)');
ylabel('amplitud');
pause(10);
