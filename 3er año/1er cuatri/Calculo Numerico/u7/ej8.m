
f = @(t,y) [y(1)*(3-0.002*y(2)); -y(2)*(0.5-0.0006*y(1))];

inter = [0 24];

y0 = [1600;800];

L = 1000;

[t,y] = rk4(f,inter,y0,L);

presa = y(:,1); %x1
depredador = y(:,2); %x2

figure(1)
plot(t,presa)
hold on
plot(t,depredador)

grid on
legend('Presa','Depredador')
xlabel('Tiempo (meses)')
ylabel('Poblacion')
title('Modelo depredador-presa')
