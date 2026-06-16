addpath('Funciones');
clc;
clear;
format long;

%-------------------------
% Datos del problema
%-------------------------

f = @(t,u) [ ...
    u(2);
    (2+0.5*t)*(exp(-t)-3*u(1)) + 0.5*u(2)/(2+0.5*t)
];

u0 = [1 0];

%=========================
% Inciso (b)
%=========================

h = 0.01;
L = round(4/h);

[t,u] = rk4(f,[0 4],u0,L);

posicion = u(end,1)
velocidad = u(end,2)

if (velocidad > 0)
  disp("En t=4 se mueve hacia la derecha");
elseif (velocidad < 0)
  disp("En t=4 se mueve hacia la izquierda");
else
  disp("En t=4 esta momentaneamente detenido");
endif

%=========================
% Inciso (c)
%=========================

L = round(10/h);

[t,u] = rk4(f,[0 10],u0,L);

v = u(:,2);

m = 2 + 0.5*t;

Ek = 0.5 .* m .* (v.^2);

Ek_media = (1/10) * trapz(t,Ek)

fprintf('\n');
fprintf('y(4) = %.10f\n',posicion);
fprintf('y''(4) = %.10f\n',velocidad);
fprintf('<Ek> = %.10f\n',Ek_media);
