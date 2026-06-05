clear;
clc;
close all;

fm = 16000;

% cant de puntos para definir H(f)
Nfft = 4096;

f = (0:Nfft-1)*(fm/Nfft);

H = zeros(1,Nfft);

%banda 1 [100,200]
idx = find(f >= 100 & f <= 200);
H(idx) = 1;

% banda 2 [1640,3028]
idx = find(f >= 1640 & f <= 3028);
H(idx) = 1;

% banda 3 [5000,6000]
idx = find(f >= 5000 & f <= 6000);
H(idx) = (f(idx)-5000)/1000;

% siimetria(para garantizar que la resp al impulso obtenida mediante ifft sea real)
for k = 2:Nfft/2
    H(Nfft-k+2) = H(k);
end


h_ideal = real(ifft(H));

% mueve el centro al medio
h_ideal = fftshift(h_ideal);

% longitud FIR finita
N = 101;
centro = floor(length(h_ideal)/2)+1;
ini = centro - floor(N/2);
fin = centro + floor(N/2);
h = h_ideal(ini:fin);

% Ventana Hamming
w = 0.54 - 0.46*cos(2*pi*(0:N-1)/(N-1));

% FIR final
h_fir = h .* w;

%resp en frecuencia
[Hfir,ff] = freqz(h_fir,1,4096,fm);

%graficos
figure;
plot(ff,abs(Hfir),'LineWidth',1.5);
grid on;
xlabel('Frecuencia (Hz)');
ylabel('|H(f)|');
title('Respuesta en frecuencia del FIR');
figure;
stem(0:N-1,h_fir);
grid on;
xlabel('n');
ylabel('h[n]');
title('Respuesta al impulso del FIR');
