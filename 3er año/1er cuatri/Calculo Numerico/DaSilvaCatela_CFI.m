addpath('Funciones');
clc;clear;
% datos

t = [0.5 1 1.5 2 2.5]';
E = [1.9238 1.4920 1.3165 1.1669 1.0955]';

% lo hago lineal para poder usar polyfit
x = log(t);
y = log(E);

% ajuste lineal
coef = polyfit(x,y,1); %es 1 xq queremos ajustar un modelo lineal

% recupero los parametros
bta = -coef(1);
E0 = exp(coef(2));

fprintf('E0 = %.10f\n',E0);
fprintf('beta = %.10f\n',bta);

Efun  = @(t) E0*t.^(-bta);
dEfun = @(t) -bta*E0*t.^(-bta-1);
% item b
p = @(t) -(dEfun(t)+0.3)./Efun(t);
q = @(t) -0.5./Efun(t);
r = @(t) exp(-0.2*t)./Efun(t);

f = @(t)[p(t) q(t) r(t)];

% condiciones de contorno

a = 0;
rob = [Efun(4) 0.1 0.1];

% cantidad inicial de subintervalos
L = 20;
fprintf('    L         eps_max\n');

for i = 1:8
    % resuelvo con la malla actual
    [t,eps] = dif_fin_rob(f,[0.5 4],a,rob,L);
    % deformacion maxima
    epsmax = max(eps);
    fprintf('%6d   %.10f\n',L,epsmax);
    % duplico la cantidad de subintervalos
    L = 2*L;
endfor
% veo q las 5 cifras exactas se encuentran en L=320 entonces
L = 320;

[t,eps] = dif_fin_rob(f,[0.5 4],a,rob,L);

epsmax = max(eps);

ind = find(eps == epsmax);
tmax = t(ind);

fprintf('deformacion max = %.5g\n',epsmax);
fprintf('ocurre en t = %.5g s\n',tmax);

%c
[S,dS,ddS] = funcion_spline(t',eps');
tt = linspace(0.5,4,1000);
deps = dS(tt);

[~,ind] = max(deps);

tmax = tt(ind);

fprintf('maxima tasa de deformacion en %.5f s\n',tmax);
