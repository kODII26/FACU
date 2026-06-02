clear;
clc;

x = [3 5 7 9]';
y = [1.2 1.7 2.0 2.1]';

%% Metodo de Lagrange

[P,L] = Lagrange(x',y');

disp('Coeficientes por Lagrange')
disp(P)

%% Metodo de coeficientes indeterminados

V = [x.^3 x.^2 x ones(length(x),1)];

coef = GaussLUPP(V,y);

disp('Coeficientes por coeficientes indeterminados')
disp(coef)

% desp me pide reducir el polinomio Pl pero ya mi vector P es de esa forma
% viendo los coeficientes obtenidos en cada inciso me doy cuenta que son iguales







