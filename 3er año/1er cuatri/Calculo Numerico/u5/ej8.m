clear;
clc;

t = [4 8 12 16 20 24];
c = [1590 1320 1000 900 650 560];

%% Linealizacion(no podemos usar polyfit directamente ya que ajusta modelos lineales

z = log(c);

%% Ajuste lineal

p = polyfit(t,z,1);

m = p(1); % pendiente
n = p(2); % ord al origen

%% Parametros del modelo

k = -m;
b = exp(n);

fprintf('b = %.4f\n',b);
fprintf('k = %.6f\n',k);

%% Inciso b

c0 = b; % solo la ord al origen ya que t=0

fprintf('\nConcentracion al final de la tormenta:\n');
fprintf('%.4f CFU/100mL\n',c0);

%% Inciso c

t200 = log(b/200)/k;

fprintf('\nTiempo para alcanzar 200 CFU/100mL:\n');
fprintf('%.4f horas\n',t200);
