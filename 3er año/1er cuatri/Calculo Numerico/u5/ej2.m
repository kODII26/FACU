% trazador natural: impone S''(x0)=S''(xn)=0
% curvatura nula en los extremos

% trazador sujeto(clamped) impone S'(x0) y S'(xn) conocidos

%el spline natural requiere únicamente los puntos a interpolar, mientras que el spline
% sujeto necesita además los valores de la derivada en los extremos del intervalo


% ---- ejer ---
% Evaluo la continiudad de la primera derivada en x=1
S0'(1)=-1
S1'(1)=b
=> b=-1

% evaluo continiudad de la 2da derivada en x=1
S0''(1)=-6
S1''(1)=2c
=> c= -3

% condicion del trazado natural: S''(x0)=S''(xn)=0
S0''(0)=0
S1''(2)=-6+6d=0
=> d=1





