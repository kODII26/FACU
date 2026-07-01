addpath('../Funciones');

% Datos del problema
Lbarra = 3;
K0 = 1;

alpha = 21;          % u(0)=21
% Extremo derecho aislado:
% u'(3)=0  -->  1*u'+0*u=0
rob = [1 0 0];

% p(x), q(x), r(x)

% -u'' = 20*sin(5(x-1))
% -u'' +0*u'+0*u -20*sin(5(x-1))=0

f = @(x) [ 0*x , 0*x , -20*sin(5*(x-1)) ];

% Cantidad de subintervalos
L = 100;
for i=1:5
    [x,u] =  dif_fin_rob(f,[0 Lbarra],alpha,rob,L);
    disp('L: '),disp(L);
    printf("%.14f\n",u(end));
    L=L*2;
endfor
%ya dejan de cambiar los 2 primeros decimales

% Inciso (a)
fprintf('Temperatura en x=3 = %.6f\n',u(end));

% Inciso (b)
[Tmax,idx] = max(u);
xmax = x(idx);

fprintf('Temperatura maxima = %.6f\n',Tmax);
fprintf('Se alcanza aproximadamente en x = %.6f\n',xmax);

% Grafico
figure(1)

plot(x,u,'b','linewidth',2)
grid on

xlabel('x')
ylabel('Temperatura')
title('Distribucion de temperatura en la barra')
