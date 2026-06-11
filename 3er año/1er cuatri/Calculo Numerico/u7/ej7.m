%transformamos el sistema en una unica funcion vectorial
%X=[x1 x2] => X'=[-tx2 tx1-tx2]
%esto es un PVI del tipo: X'=F(t,X)
%que puede resolverle con Euler

f = @(t,y) [-t*y(2); t*y(1)-t*y(2)];

inter = [0 20];

y0 = [1; -1];

h = 0.05;

L = (inter(2)-inter(1))/h;

[t,y] = euler(f,inter,y0,L);

x1 = y(:,1); %guarda toda la evolucion temporal de x1
x2 = y(:,2);

figure(1)
plot(x1,x2)
grid on

xlabel('x_1')
ylabel('x_2')
title('Trayectoria de la particula')
