x0=1.5;
tol=1e-3;
kmax=100;

g1=@(x) 0.5.*(10-x.^3).^0.5;
g2=@(x) (10./(4+x)).^0.5;

[x_aprox1, h1] = puntofijo(g1, x0, kmax, tol);
disp(['Aproximación obtenida: ', num2str(x_aprox1)]);
disp(['Cantidad de iteraciones: ', num2str(length(h1) - 1)]);

%Puntofijo guarda las iteraciones en h pero cuando inicializas guarda x0 en h
%esto no genera una iteracion y si genera +1 de longitud en el vector
%por eso siempre hay que restarle 1

% 4. Evaluamos la segunda función g2(x)
disp('--- Evaluando g2(x) ---');
[x_aprox2, h2] = puntofijo(g2, x0, kmax, tol);
disp(['Aproximación obtenida: ', num2str(x_aprox2)]);
disp(['Cantidad de iteraciones: ', num2str(length(h2) - 1)]);

