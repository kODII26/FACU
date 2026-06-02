1;
addpath('..\Funciones creadas');

clear;
clc;

fm = 100;
T = 1/fm;

t = 0:T:1-T;

f = 10;

x = sin(2*pi*f*t);

figure;
plot(t,x);

title('Señal original');
xlabel('Tiempo');
ylabel('Amplitud');

grid on;

X = fft(x);
N = length(x);

freq = (0:N-1)*(fm/N);

figure;
plot(freq,abs(X));

xlim([0 50]);

grid on;

title('Magnitud FFT');

n0 = 10;

k = 0:N-1;
X_ret = X .* exp(-1j*2*pi*k*n0/N); % retardo la senal 10 muestras
x_ret = ifft(X_ret);

figure;

plot(t,x,'b');

hold on;

plot(t,real(x_ret),'r');

legend('Original','Retardada');

grid on;

figure;

plot(freq,abs(X));

hold on;

plot(freq,abs(X_ret)); % picos en 10 y 90 debido a que la fft no muestrea frecuencias negativos
% una senal original de 10hz tiene frecuencias +10hz y - 10hz por lo tanto se hace
% para la senal negativa: fm-f = 100+(-10) = 90

legend('Original','Retardada');

% Se verificó la propiedad de retardo temporal de la TDF. La aplicación
% de un término exponencial complejo en el dominio frecuencial produjo
% un desplazamiento temporal de la señal reconstruida mediante la
% transformada inversa. En este caso particular, el retardo aplicado
% coincidió con un período completo de la senoide, por lo que la señal
% resultante se superpone con la original. Sin embargo, el efecto se observa
% en la fase espectral, mientras la magnitud permanece inalterada.


% cambio de fase
%figure;
%plot(freq, angle(X))
%hold on
%plot(freq, angle(X_ret))
%grid on;

% ver senal con -10hz y +10hz
X = fft(x);

X2 = fftshift(X);

f = (-N/2:N/2-1)*(fm/N);

plot(f,abs(X2))
