%parametros que da la consigna
a=0.5;
N=10;
n=0:N-1;

hA=sin(8.*n);
hB=a.^n;

% entrada x[n] = delta[n] - a delta[n-1]
x=zeros(1,N);
x(1)=1; %x(0)
x(2)=-a; %x(1)

% calculo conv en cascada
w_1=conv(x,hA);
y_1=conv(w_1,hB);

% calculo conv en cascada invertida
w_2= conv(x,hB);
y_2=conv(w_2,hA);

disp("Salida con orden original:");
disp(y_1);

disp("Salida con orden invertido:");
disp(y_2);

% comprobamos si las salidas son iguales
diferencia = max(abs(y_1 - y_2));
disp(['Diferencia max entre ambas conexiones: ', num2str(diferencia)]);

figure;
subplot(2,1,1);
stem(y_1, 'filled', 'b');
title('Salida y[n] - Conexión Original (hA -> hB)');

subplot(2,1,2);
stem(y_2, 'filled', 'r');
title('Salida y[n] - Conexión Invertida (hB -> hA)');


