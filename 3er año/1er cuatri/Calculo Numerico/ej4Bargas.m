addpath('Funciones');
clear;
N=41; % puntos
h=1/(N-1); % 41 puntos -> 40 subintervalos
x=linspace(0,1,41);

xi = x(2:end-1); % puntos interiores, sin x0 y x40

%armo la matriz
n = 39;
A = 2*eye(n) - diag(ones(n-1,1),1) - diag(ones(n-1,1),-1);
%armo b
b = h^2 * 20 * exp(-10*(xi-0.7).^2)';

% la matriz es 39x39 porque hay 2 incognitas que ya conocemos
% las 2 incognitas que ya tenemos las despejo de la ec y pasan sumando al b
b(1)= b(1)+5;
b(end)= b(end) +6;

maxit=2000;
tol=1e-6;
x0=zeros(n,1);
[x,it,r_h]=gauss_seidel(A,b,x0,maxit,tol);
disp(it);

fprintf('La temperatura en el punto medio de la barra es: %.6f\n', x(20));

