
x=[ 1 1 2 1];
h=[ 2 5 4 1];

disp('Calculado manualmente: ');
y_manual=conv_lineal(x,h);
disp(y_manual);


disp('Con comando conv: ');
y_conv= conv(x,h);
disp(y_conv);

disp('Con comando filter');
A = 1;
B = h;

x_extendido = [x zeros(1, length(x)-1)]; %agrego ceros alfinal
% debido a que filter calcula la respuesta del sistema mientras exista entrada

y_filter = filter(B, A, x_extendido);
disp(y_filter)


figure;
% 1: Manual
subplot(3,1,1);
stem(y_manual, 'filled', 'b');
title('Convolución Manual');
grid on;

% 2: Función conv()
subplot(3,1,2);
stem(y_conv, 'filled', 'r');
title('Convolución Nativa (conv)');
grid on;

% 3: Función filter()
subplot(3,1,3);
stem(y_filter, 'filled', 'g');
title('Convolución con filter()');
grid on;
