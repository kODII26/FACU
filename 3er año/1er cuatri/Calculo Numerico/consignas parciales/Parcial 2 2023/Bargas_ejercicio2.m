clc;
clear all;
format long;
inter=[0,120];
L=120;
I=4250;
P=3000;
E=2.1e6;

h=0.05;
%subinter=(120-0)/h;
subinter=60;

f = @(x,y) ([y(2);(P.*(L-x)).*((1+((y(2)).^2)).^(3/2))/(E*I)]);
y0=[0,0];


[t,y]=rk4(f, inter, y0, subinter);

figure(1)
plot(y(:,1)) %el desplazamiento
figure(2)
plot(y(:,2)) %la pendiente

max1=y(1,1);
max2=0;
for i=1:length(t)
  if (y(i,1)>max1)
    max1=y(i,1);
    max2=i;
  endif
end
disp("El maximo desplazamiento es:")
 max1

 %para ver la pendiente
posi= t;
poli = polyfit(t',y(:,2),2);
g = @(x) poli(3) + (poli(2).*x) + (poli(1).*x.^2)-0.0019 ;

figure(3)
plot(t,g(t));

%una vez graficado ya vemos donde corta en 0 el valor de la pendiente
[pbis, rh, it, t] = biseccion(g, 64.3, 64.4, 400, 1e-5);
pbis






