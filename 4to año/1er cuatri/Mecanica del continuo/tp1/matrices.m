clear; clc;

%% -----------------------------
% DATOS DEL PROBLEMA
%% -----------------------------
E = 600;
A = 0.25;
rho = 1;

%% -----------------------------
% NODOS (x,y)
% (TENÉS QUE COMPLETAR SEGÚN LA FIGURA)
%% -----------------------------
% Ejemplo (ajustar a tu geometría real)
nodes = [
    0   0;   % 1
    10  0;   % 2
    5  5;   % 3
    20  0;   % 4
    15  15;   % 5
    25  15;   % 6
    20  20;   % 7
    30  30;   % 8
    35  15;   % 9
    40  20;   % 10
    45  15;   % 11
    40  0;   % 12
    50 0;   % 13
    55 5;   % 14
    60 0;   % 15
];

n_nodes = size(nodes,1);
ndof = 2*n_nodes;

%% -----------------------------
% BARRAS (i, j)
% (esto SÍ está en tu tabla del TP)
%% -----------------------------
bars = [
    1 2;
    1 3;
    2 4;
    4 6;
    4 5;
    5 2;
    2 3;
    5 6;
    6 7;
    3 5;
    5 7;
    7 8;
    15 13;
    15 14;
    14 11;
    11 10;
    10 8;
    13 12;
    12 9;
    12 11;
    11 13;
    13 14;
    11 9;
    9 10;
    6 8;
    9 8
];

n_bars = size(bars,1);

%% -----------------------------
% MATRICES GLOBALES
%% -----------------------------
K = zeros(ndof, ndof);
M = zeros(ndof, ndof);

%% -----------------------------
% LOOP DE BARRAS
%% -----------------------------
for e = 1:n_bars

    i = bars(e,1);
    j = bars(e,2);

    xi = nodes(i,1); yi = nodes(i,2);
    xj = nodes(j,1); yj = nodes(j,2);

    dx = xj - xi;
    dy = yj - yi;
    L = sqrt(dx^2 + dy^2);

    c = dx / L;
    s = dy / L;

    %% Rigidez barra
    k = (E*A)/L;

    Ke = k * [
        c^2   c*s  -c^2  -c*s;
        c*s   s^2  -c*s  -s^2;
       -c^2  -c*s   c^2   c*s;
       -c*s  -s^2   c*s   s^2
    ];

    %% Masa barra
    m = rho*A*L;

    %% Masa lumped (mitad a cada nodo)
    mi = m/2;
    mj = m/2;

    %% DOFs
    dof = [
        2*i-1  2*i  2*j-1  2*j
    ];

    %% ENSAMBLE K
    K(dof,dof) = K(dof,dof) + Ke;

    %% ENSAMBLE M (diagonal)
    M(2*i-1,2*i-1) += mi;
    M(2*i,2*i)     += mi;

    M(2*j-1,2*j-1) += mj;
    M(2*j,2*j)     += mj;

end

%% -----------------------------
% CONDICIONES DE BORDE
% Nodo 1 y 15 fijos
%% -----------------------------
fixed = [
    1 2 ...         % nodo 1
    2*15-1 2*15     % nodo 15
];

for d = fixed
    K(d,:) = 0;
    K(:,d) = 0;
    K(d,d) = 1;

    M(d,:) = 0;
    M(:,d) = 0;
    M(d,d) = 1;
end

%% -----------------------------
% RESULTADOS
%% -----------------------------
disp('Matriz de rigidez K:');
disp(K);

disp('Matriz de masa M:');
disp(M);
