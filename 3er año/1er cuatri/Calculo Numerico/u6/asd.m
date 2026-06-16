addpath('Funciones');

%-----------------------------------
% Sistema equivalente de primer orden
%-----------------------------------

f = @(t,u) [ ...
    u(2);
    ((exp(-t)-3*u(1))*(2+0.5*t)^2 + 0.5*u(2))/(2+0.5*t)
];

u0 = [1 0];

%===================================
% Inciso (b)
%===================================

tol = 0.5e-7;

h = 0.1;
err = inf;

while (err > tol)

    L = round(4/h);

    [t,u] = rk4(f,[0 4],u0,L);

    pos1 = u(end,1);
    vel1 = u(end,2);

    h2 = h/2;

    L2 = round(4/h2);

    [t,u] = rk4(f,[0 4],u0,L2);

    pos2 = u(end,1);
    vel2 = u(end,2);

    err = max(abs([pos2-pos1 , vel2-vel1]));

    h = h2;

end

posicion = pos2;
velocidad = vel2;

fprintf('h utilizado = %.10f\n',h);
fprintf('y(4) = %.7f\n',posicion);
fprintf('y''(4) = %.7f\n',velocidad);

if (velocidad > 0)
  disp('En t=4 se mueve hacia la derecha');
elseif (velocidad < 0)
  disp('En t=4 se mueve hacia la izquierda');
else
  disp('En t=4 esta momentaneamente detenido');
endif

%===================================
% Inciso (c)
%===================================

L = round(10/h);

% Simpson compuesto necesita cantidad PAR de subintervalos
if rem(L,2)
  L = L + 1;
endif

[t,u] = rk4(f,[0 10],u0,L);

v = u(:,2);

m = 2 + 0.5*t;

Ek = 0.5 .* m .* (v.^2);

Ek_media = simpsoncomp(t,Ek)/10;

fprintf('<Ek> = %.8f\n',Ek_media);
