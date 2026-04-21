A = [3/4, 1/6;
     1/4, 1/4];

% Autovalores y autovectores
[V,D] = eig(A);
%D es diagonal y en su diagonal están los autovalores.
%V tiene en sus columnas los autovectores asociados.

autovalores = diag(D)

% Radio espectral
rho = max(abs(autovalores))

% Verificacion de convergencia
if rho < 1
  disp("A es convergente")
else
  disp("A no es convergente")
endif

%una matriz es convergente si y sólo si su radio espectral es menor que 1
