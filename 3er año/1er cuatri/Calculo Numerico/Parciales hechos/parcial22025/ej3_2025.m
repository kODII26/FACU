addpath('Funciones');
clc; clear;
t = linspace(0, 2*pi, 8);

x1 = 6*cos(t) - 3*cos(2*t);
x2 = 6*sin(t) - 3*sin(2*t);

dx1 = @(t) -6*sin(t) + 6*sin(2*t);
dx2 = @(t) 6*cos(t) - 6*cos(2*t);

df1_x1 = dx1(t(1));
df2_x1 = dx1(t(end));

df1_x2 = dx2(t(1));
df2_x2 = dx2(t(end));

[~, dSx1] = funcion_spline(t, x1, df1_x1, df2_x1);
[~, dSx2] = funcion_spline(t, x2, df1_x2, df2_x2);

t_eval = 4;

v_aprox = sqrt( (dSx1(t_eval))^2 + (dSx2(t_eval))^2 );
v_real = sqrt( dx1(t_eval)^2 + dx2(t_eval)^2 );

error = abs(v_real - v_aprox);
% error abs 0.071300 -> 2do decimal ult cifra confiable
%% 10,98
%% 0,071
printf("vel aprox en t = 4: %.2f\n", v_aprox);
printf("vel exacta en t = 4: %.2f\n", v_real);
printf("error absoluto: %.3f\n", error);

