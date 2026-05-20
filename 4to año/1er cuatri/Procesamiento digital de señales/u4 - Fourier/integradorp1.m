# definicion de los parametros iniciales (fs = 1000 hz)
fs1 = 1000;
# creamos el vector de tiempo de 1 segundo de duracion
t1 = 0:1/fs1:0.999;
n1 = length(t1);

# generamos la combinacion lineal de las 3 senoides
# a1=5, a2=3, a3=2 y f1=50, f2=120, f3=280
s1 = 5*sin(2*pi*50*t1) + 3*sin(2*pi*120*t1) + 2*sin(2*pi*280*t1);

# calculamos la tdf con la funcion rapida (fft) y extraemos su magnitud
tdf1 = fft(s1);
mag1 = abs(tdf1);

# creamos el eje x de frecuencias reales y calculamos la resolucion
frec1 = (0:n1-1) * (fs1/n1);
# resolucion frecuencial: df = fs1/n1 = 1000/1000 = 1 hz

# graficamos la señal original sin aliasing
figure(1);
subplot(2,1,1);
plot(frec1, mag1, 'b');
title('espectro con fs = 1000 hz');
xlabel('frecuencia (hz)');
ylabel('magnitud');
axis();
grid on;

# --- reduccion de la frecuencia de muestreo (fs = 200 hz) ---
fs2 = 200;
# mantenemos la duracion en 1 segundo
t2 = 0:1/fs2:0.995;
n2 = length(t2);

# generamos la misma señal pero con menos puntos de muestreo
s2 = 5*sin(2*pi*50*t2) + 3*sin(2*pi*120*t2) + 2*sin(2*pi*280*t2);

# calculamos la nueva tdf y su magnitud
tdf2 = fft(s2);
mag2 = abs(tdf2);
frec2 = (0:n2-1) * (fs2/n2);

# graficamos el resultado afectado por aliasing
subplot(2,1,2);
plot(frec2, mag2, 'r');
title('espectro con fs = 200 hz (efecto aliasing)');
xlabel('frecuencia (hz)');
ylabel('magnitud');
axis();
grid on;
pause(10);
