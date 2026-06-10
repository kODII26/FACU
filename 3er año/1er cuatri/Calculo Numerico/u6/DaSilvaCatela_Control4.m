addpath('../Funciones');

m = 68.1;
cd = 0.25;
g = 9.81;

v = @(t) sqrt(g*m/cd).*tanh(sqrt(g*cd/m).*t);

%pongo muchos subintervalos para mayor precision
L = 1000;
x = linspace(0,10,L+1);
y = v(x);

dist_seg10 = trapcomp(x,y);
fprintf('distancia a los 10seg: %.6g\n',dist_seg10);

%item b
Iexacta = (m/cd)*log(cosh(sqrt(g*cd/m)*5));%integral en 5s

x = linspace(0,5,6);
y = v(x);

%trap comp de 5 subintervalos
Itrap = trapcomp(x,y);

%gauss comp 2 puntos 5 subintervalos
Igauss = cuad_gauss_c(v,0,5,5,2);

erR_trap = abs(Iexacta-Itrap)/abs(Iexacta);
erR_gauss = abs(Iexacta-Igauss)/abs(Iexacta);

% cifrasExactas= -log10(2*errorRelativo)
cif_trap = -log10(2*erR_trap);
cif_gauss = -log10(2*erR_gauss);

fprintf('cifras trapecio : %d\n',floor(cif_trap));
fprintf('cifras gauss :%d\n',floor(cif_gauss));
