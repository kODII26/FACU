clear;
clc;
close all;

%ruido de linea: 50hz
%banda rechazada: entre 48 y 52 hz

fs = 300; % frecuencia de muestreo
f1 = 48; % inicio banda rechazada
f2 = 52; % fin banda rechazada

N = 41; % cantidad de coeficientes (impar)
M = (N-1)/2;

n = -M:M;

% frecuencias que delimitan la banda rechazada
w1 = 2*pi*f1/fs;
w2 = 2*pi*f2/fs;

% respuesta impulsional ideal rechaza-banda
h = zeros(size(n));

for k = 1:length(n)

    if n(k)==0
        h(k) = 1 - (w2-w1)/pi;
    else
        h(k) = (sin(w1*n(k)) - sin(w2*n(k))) /(pi*n(k));
    end

end

% ventanas
w_rect = ones(1,N);
w_hamm = 0.54 - 0.46*cos(2*pi*(0:N-1)/(N-1));
w_black = 0.42 -0.5*cos(2*pi*(0:N-1)/(N-1)) +0.08*cos(4*pi*(0:N-1)/(N-1));

% filtros finales
h_rect = h .* w_rect;
h_hamm = h .* w_hamm;
h_black = h .* w_black;

% calculo respuestas en frecuencia
[Hrect,f] = freqz(h_rect,1,2048,fs);
[Hhamm,~] = freqz(h_hamm,1,2048,fs);
[Hblack,~] = freqz(h_black,1,2048,fs);

figure

plot(f,20*log10(abs(Hrect)+eps),'LineWidth',1.5)
hold on
plot(f,20*log10(abs(Hhamm)+eps),'LineWidth',1.5)
plot(f,20*log10(abs(Hblack)+eps),'LineWidth',1.5)

grid on

xlabel('Frecuencia (Hz)')
ylabel('Magnitud (dB)')

legend('Rectangular','Hamming','Blackman')
title('Comparación de ventanas')
