clear;
clc;
close all;

%ruido de linea: 50hz
%banda rechazada: entre 48 y 52 hz

% filtro fir rechaza banda

fm = 300;
f1 = 48;
f2 = 52;

% frecuencias angulares
w1 = 2*pi*f1/fm;
w2 = 2*pi*f2/fm;

%item a
N = 41;
M = (N-1)/2;
n = -M:M;

% respuesta impulsional ideal
h = zeros(size(n));

for k = 1:length(n)
    if n(k) == 0
        h(k) = 1 - (w2-w1)/pi;
    else
        h(k) = (sin(w1*n(k)) - sin(w2*n(k))) / (pi*n(k));
    end
end

% ventanas
w_rect  = ones(1,N);
w_hamm = 0.54 - 0.46*cos(2*pi*(0:N-1)/(N-1));
w_black = 0.42 - 0.5*cos(2*pi*(0:N-1)/(N-1)) + 0.08*cos(4*pi*(0:N-1)/(N-1));

% filtros FIR
h_rect  = h .* w_rect;
h_hamm  = h .* w_hamm;
h_black = h .* w_black;

% respuestas en frecuencia
[Hrect,f]  = freqz(h_rect ,1,2048,fm);
[Hhamm,~]  = freqz(h_hamm ,1,2048,fm);
[Hblack,~] = freqz(h_black,1,2048,fm);

figure(1)

plot(f,20*log10(abs(Hrect)+eps),'LineWidth',1.5)
hold on
plot(f,20*log10(abs(Hhamm)+eps),'LineWidth',1.5)
plot(f,20*log10(abs(Hblack)+eps),'LineWidth',1.5)

grid on

xlabel('Frecuencia (Hz)')
ylabel('Magnitud (dB)')
title('Comparación de ventanas (N = 41)')

legend('Rectangular','Hamming','Blackman')

%Compare los resultados obtenidos con diferentes
%ventanas de truncado
Ns = [21 41 81]; % tomo 3 N cualquiera

figure(2)
hold on

for N = Ns
    M = (N-1)/2;
    n = -M:M;
    % respuesta impulsional ideal
    h = zeros(size(n));
    for k = 1:length(n)
        if n(k)==0
            h(k) = 1 - (w2-w1)/pi;
        else
            h(k) = (sin(w1*n(k)) - sin(w2*n(k))) /(pi*n(k));
        end
    end

    % ventana Hamming
    w = 0.54 - 0.46*cos(2*pi*(0:N-1)/(N-1));
    % FIR final
    h_fir = h .* w;
    % respuesta en frecuencia
    [H,f] = freqz(h_fir,1,2048,fm);
    plot(f,20*log10(abs(H)+eps),'LineWidth',1.5)
end

grid on

xlabel('Frecuencia (Hz)')
ylabel('Magnitud (dB)')
title('Comparación para distintas longitudes (ventana Hamming)')

legend('N = 21','N = 41','N = 81')

 %diferentes cantidades de muestras en la respuesta al
%impulso
figure(3)
for i = 1:length(Ns)
    N = Ns(i);
    M = (N-1)/2;
    n = -M:M;
    h = zeros(size(n));
    for k = 1:length(n)
        if n(k)==0
            h(k) = 1 - (w2-w1)/pi;
        else
            h(k) = (sin(w1*n(k)) - sin(w2*n(k))) /(pi*n(k));
        end
    end

    subplot(length(Ns),1,i)

    stem(n,h,'filled')

    grid on

    title(['Respuesta al impulso ideal - N = ' num2str(N)])
    xlabel('n')
    ylabel('h[n]')

end
