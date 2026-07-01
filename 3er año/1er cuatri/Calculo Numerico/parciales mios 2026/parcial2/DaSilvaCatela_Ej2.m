addpath('Funciones');

f = @(t,u) [u(2); ((exp(-t)-3.*u(1)).*(2+0.5.*t).^2+0.5.*u(2))/(2+0.5.*t)];

u0 = [1 0];

inter= [0 4];
h = 0.02;
L = (4-0)/h;

[t,u] = rk4(f,inter,u0,L);

posicion = u(end,1);
velocidad = u(end,2);
fprintf('posicion y(4) = %.7f\n',posicion);
fprintf('velocidad y prima(4) = %.7f\n',velocidad);

%si la velocidad es positiva va hacia la derecha
%de lo contrario va hacia la izq
%es positiva por lo tanto se mueve hacia la derecha

inter2=[0 10];
L2 = (10-0)/h;

[t,u] = rk4(f,inter2,u0,L2);

v = u(:,2);

m = 2 + 0.5*t;

Ek = 0.5 .* m .* (v.^2);

Ek_media =simpsoncomp(t,Ek)/10;


fprintf('<Ek> = %.8g\n',Ek_media);
