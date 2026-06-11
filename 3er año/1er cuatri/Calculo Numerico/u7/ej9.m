

f = @(t,y) [y(2) ; y(3); -4.*sin(t)-2.*cos(t)-4.*y(3)-5.*y(2)-2.*y(1)];

inter= [0 15];
y0=[1 0 -1];
L=1000;

[t,y]=rk4(f, inter, y0, L);

x1 = y(:,1);
x2 = y(:,2);
x3 = y(:,3);

%item b
y25 = interp1(t,x1,2.5); %interpola la sol ya que prob. no exista en t=2.5s
fprintf('y(2.5) = %.6g\n',y25);
%% grafico

figure(1)
plot(t,x1)
grid on
xlabel('t')
ylabel('y(t)')
title('Solucion del PVI')
%% inciso c

fprintf('Cantidad de ceros de y''(t):5 %d\n');

%veo 5 ceros, cada maximo y minimo de y(t) hace que se anule su derivada
