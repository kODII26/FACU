addpath('../Funciones creadas');
T=0.001;
fm=1/T;

sen1=generar_senoidal(10, fm, 0, 0, 1);
sen2=generar_senoidal(20, fm, 0, 0, 1);
s=sen1+4*sen2;

N=length(s);
S=fft(s);
% delta F = fm/N
f= (0:N/2-1)*(fm/N);
magnitud=abs(S);

% Grafico
#figure;
#plot(f, magnitud(1:N/2)); % grafico la mitad ya que la segunda mitad
% es el espejo de la primera
#xlabel('Frecuencia [Hz]');
#ylabel('|S[k]|');
#title('Espectro de magnitud');
#grid on;
% el espectro de magnitud muestra qué cantidad de cada frecuencia existe dentro de la señal
% por eso vemos un pico en 10hz y un pico 4 veces mayor en 20 hz
% y en el resto de frecuencias 0


% Parseval

energia_tiempo = sum(s.^2);

energia_frecuencia = (1/N)*sum(abs(S).^2);

disp(energia_tiempo)
disp(energia_frecuencia)



 % item 1
s2= s+4;
S2=fft(s2);
magnitud2=abs(S2);
% Grafico
figure;
plot(f, magnitud2(1:N/2));
xlabel('Frecuencia [Hz]');
ylabel('|S[k]|');
title('Espectro de magnitud');
grid on;

% ahora en el grafico vemos que hay un pico enorme en 0hz
% porque el +4 agrega un componente constante y eso corresponde
% a 0 hz

% item 2

sen3=generar_senoidal(11, fm, 0, 0, 1);
s3= sen1+4*sen3+4;
S3= fft(s3);

magnitud3=abs(S3);
% Grafico
figure;
plot(f, magnitud3(1:N/2));
xlabel('Frecuencia [Hz]');
ylabel('|S[k]|');
title('Espectro de magnitud');
grid on;

% item 4

sen1_2s = generar_senoidal(10, fm, 0, 0, 2);
sen2_2s = generar_senoidal(20, fm, 0, 0, 2);

s4 = sen1_2s + 4*sen2_2s;

N4 = length(s4);

S4 = fft(s4);

magnitud4 = abs(S4);

f4 = (0:N4/2-1)*(fm/N4);

figure;
plot(f4, magnitud4(1:N4/2));

xlabel('Frecuencia [Hz]');
ylabel('|S[k]|');
title('Espectro de magnitud - t=[0,2)');
grid on;














