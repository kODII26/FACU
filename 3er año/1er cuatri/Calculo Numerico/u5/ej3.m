clear;
clc;
close all;

%% ==========================
%% Datos originales
%% ==========================

x = linspace(-1,1,21);
y = sin(2*pi*x);

%% Polinomio de Lagrange

[P,L] = Lagrange(x,y);

%% Spline cúbico natural

[a,b,c,d] = cubic_spline_natural(x,y);

%% Malla fina para graficar

xx = linspace(-1,1,1000);

%% Evaluaciones

yf = sin(2*pi*xx);

yL = polyval(P,xx);

yS = spline_eval(xx,x,a,b,c,d);

%% Gráfico

figure(1)

plot(xx,yf,'k','linewidth',2)
hold on
plot(xx,yL,'r--','linewidth',2)
plot(xx,yS,'b','linewidth',2)
plot(x,y,'ko','markersize',5)

grid on

legend('f(x)','Lagrange','Spline natural','Datos')

title('Datos originales')

xlabel('x')
ylabel('y')

%% ==========================
%% Datos perturbados
%% ==========================

yp = zeros(size(x));

for i=1:length(x)
  yp(i) = sin(2*pi*x(i)) + (-1)^(i+1)*1e-4;
endfor

%% Lagrange perturbado

[Pp,Lp] = Lagrange(x,yp);

%% Spline perturbado

[a2,b2,c2,d2] = cubic_spline_natural(x,yp);

%% Evaluaciones

yLp = polyval(Pp,xx);

ySp = spline_eval(xx,x,a2,b2,c2,d2);

%% Gráfico

figure(2)

plot(xx,yf,'k','linewidth',2)
hold on
plot(xx,yLp,'r--','linewidth',2)
plot(xx,ySp,'b','linewidth',2)
plot(x,yp,'ko','markersize',5)

grid on

legend('f(x)','Lagrange perturbado','Spline perturbado','Datos')

title('Datos perturbados')

xlabel('x')
ylabel('y')
