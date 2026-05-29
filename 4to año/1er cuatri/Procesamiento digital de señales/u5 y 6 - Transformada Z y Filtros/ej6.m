clear;
clc;
close all;

% Frecuencia de muestreo
fs = 16000;

% Cantidad de puntos para definir H(f)
Nfft = 4096;

% Vector de frecuencias
f = (0:Nfft-1)*(fs/Nfft);

% Respuesta en frecuencia deseada
H = zeros(1,Nfft);

% Banda 1: [100,200] Hz
idx = find(f >= 100 & f <= 200);
H(idx) = 1;

% Banda 2: [1640,3028] Hz
idx = find(f >= 1640 & f <= 3028);
H(idx) = 1;

% Banda 3: [5000,6000] Hz
idx = find(f >= 5000 & f <= 6000);
H(idx) = (f(idx)-5000)/1000;

% Simetría para obtener h[n] real
for k = 2:Nfft/2
    H(Nfft-k+2) = H(k);
end

% Respuesta al impulso ideal
h_ideal = real(ifft(H));

% Centrar respuesta
h_ideal = fftshift(h_ideal);

% Longitud FIR
N = 101;

% Recortar parte central
centro = floor(length(h_ideal)/2)+1;
ini = centro - floor(N/2);
fin = centro + floor(N/2);

h = h_ideal(ini:fin);

% Ventana Hamming
w = 0.54 - 0.46*cos(2*pi*(0:N-1)/(N-1));

% FIR final
h_fir = h .* w;

% Respuesta en frecuencia
[Hfir,ff] = freqz(h_fir,1,4096,fs);

% Gráfico magnitud
figure;
plot(ff,abs(Hfir),'LineWidth',1.5);
grid on;
xlabel('Frecuencia (Hz)');
ylabel('|H(f)|');
title('Respuesta en frecuencia del FIR');

% Respuesta al impulso
figure;
stem(0:N-1,h_fir);
grid on;
xlabel('n');
ylabel('h[n]');
title('Respuesta al impulso del FIR');
