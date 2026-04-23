x = [1 1 2 1];
h = [2 5 4 1];

y = conv_circular(x, h);

disp("x =");
disp(x);

disp("h =");
disp(h);

disp("Convolucion circular:");
disp(y);


n = 0:length(x)-1;
figure(1);

subplot(3,1,1);
stem(n, x, "filled");
title("Señal x[n]");
xlabel("n");
ylabel("x[n]");
grid on;

subplot(3,1,2);
stem(n, h, "filled");
title("Señal h[n]");
xlabel("n");
ylabel("h[n]");
grid on;

subplot(3,1,3);
stem(n, y, "filled");
title("Convolucion circular y[n]");
xlabel("n");
ylabel("y[n]");
grid on;
