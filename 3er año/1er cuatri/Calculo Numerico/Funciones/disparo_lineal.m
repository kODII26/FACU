function [x,y]=disparo_lineal(f,inter,yc,L)
%-------------------------------------------------------------
% Metodo del disparo lineal para resolver el PVC:
%
%   y'' = p(x)y' + q(x)y + r(x)
%
% con condiciones de borde
%
%   y(a)=alpha
%   y(b)=beta
%
% Entradas:
%   f     -> funcion que devuelve [p q r]
%   inter -> intervalo [a b]
%   yc    -> [alpha beta]
%   L     -> cantidad de subintervalos para RK4
%
% Salidas:
%   x -> nodos
%   y -> solucion aproximada del PVC
%-------------------------------------------------------------


%=============================================================
% 1) Separamos las funciones p(x), q(x) y r(x)
%=============================================================

p = @(x) f(x)(:,1);   % coeficiente de y'
q = @(x) f(x)(:,2);   % coeficiente de y
r = @(x) f(x)(:,3);   % termino independiente


%=============================================================
% 2) Construimos el sistema de 4 ecuaciones de primer orden.
%
% Vamos a integrar simultaneamente dos disparos:
%
% Disparo 1:
%   y1(a)=alpha
%   y1'(a)=0
%
% Disparo 2:
%   y2(a)=alpha
%   y2'(a)=1
%
% Definimos:
%
% y(1)=y1
% y(2)=y2
% y(3)=y1'
% y(4)=y2'
%=============================================================

F = @(x,y) [

    % y1' = y3
    y(3);

    % y2' = y4
    y(4);

    % y3' = p*y3 + q*y1 + r
    % (segunda derivada del disparo 1)
    p(x)*y(3) + q(x)*y(1) + r(x);

    % y4' = p*y4 + q*y2 + r
    % (segunda derivada del disparo 2)
    p(x)*y(4) + q(x)*y(2) + r(x)

];


%=============================================================
% 3) Definimos las condiciones iniciales de ambos disparos.
%
% y1(a)=alpha
% y2(a)=alpha
%
% y1'(a)=0
% y2'(a)=1
%=============================================================

y0 = [

    yc(1);     % y1(a)=alpha

    yc(1);     % y2(a)=alpha

    0;         % pendiente inicial del primer disparo

    1          % pendiente inicial del segundo disparo

];


%=============================================================
% 4) Integramos ambos problemas de valor inicial
% mediante Runge-Kutta.
%
% RK4 devuelve una matriz:
%
% columna 1 -> y1
% columna 2 -> y2
% columna 3 -> y1'
% columna 4 -> y2'
%=============================================================

[x,yd] = rk4(F,inter,y0,L);


%=============================================================
% 5) Calculamos lambda.
%
% Queremos una combinación lineal
%
% y = lambda*y1 + (1-lambda)*y2
%
% tal que
%
% y(b)=beta
%
% Despejando:
%
% lambda=(beta-y2(b))/(y1(b)-y2(b))
%=============================================================

lambda = (yc(2)-yd(end,2)) / (yd(end,1)-yd(end,2));


%=============================================================
% 6) Construimos la solución final.
%
% En cada punto del intervalo mezclamos ambos disparos
% utilizando el lambda calculado.
%
% Esta nueva curva cumple:
%
% y(a)=alpha
% y(b)=beta
%
% y además satisface la ecuación diferencial.
%=============================================================

y = lambda*yd(:,1) + (1-lambda)*yd(:,2);

end
