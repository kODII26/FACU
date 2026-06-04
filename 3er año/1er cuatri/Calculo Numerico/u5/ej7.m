
x=[-1 0 1 2];
y=[-1.1 -0.4 -0.9 -2.7];

Y= log(-y);

p = polyfit(x,Y,2); % polyfit devuelve vector con los coef.

a = p(1);
b = p(2);
c = p(3);

fprintf('a = %.6f\n',a);
fprintf('b = %.6f\n',b);
fprintf('c = %.6f\n',c);

% graficar
xx=linspace(-1.5,2.5,1000);
yy=-exp(polyval(p,xx));
figure

plot(x,y,'ro','markersize',8)
hold on

plot(xx,yy,'b','linewidth',2)

grid on

xlabel('x')
ylabel('y')

legend('Datos','Modelo')

title('Ajuste exponencial')

