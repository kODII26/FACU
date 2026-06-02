function Q = trapcomp(x,y)
%
% function Q = trapcomp(x,y)
%
% Regla del trapecio compuesta para aproximar
% la integral de una funcion f en el intervalo
% [x(1), x(end)]. Se supone que y(i) = f(x(i)).
% Calculamos la cantidad L de subintervalos
% que determinan los datos
L = numel(x) - 1;
% Calculamos un vector que tiene la longitud
% de cada uno de los L subintervalos
deltax = diff(x); % deltax(i) = x(i+1)-x(i)
% Ahora aplicamos la regla del trapecio en
% cada intervalo [x(i),x(i+1)], para i = 1,2,...,L
Q = 0;
for i = 1:L
Q = Q + .5*deltax(i)*(y(i)+y(i+1));
end
