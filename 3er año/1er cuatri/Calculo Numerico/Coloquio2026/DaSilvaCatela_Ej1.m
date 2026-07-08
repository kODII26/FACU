
addpath('../Funciones')

R = 0.5;
C = 2;
tDatos = [1 2 3 4 5];
LDatos = [0.5 0.8 1.0 1.1 1.2];

[Lfun,dLfun,~] = funcion_spline(tDatos,LDatos);

E = @(t) cos(pi*t/2);

coefP = @(t) -(dLfun(t)+R)./Lfun(t);
coefQ = @(t) -1./(C*Lfun(t));
coefR = @(t) E(t)./Lfun(t);
coef = @(t) [coefP(t) coefQ(t) coefR(t)];


intervalo = [1 5];
qInicial = 2;

% condicion robin
% L(5) I(5)=0.2  ->  q'(5)=0.2/L(5)
robin = [1 0 0.2/Lfun(5)];


N = 80;
[t,q] = dif_fin_rob(coef,intervalo,qInicial,robin,N);

%item a

h = t(2)-t(1);
k = find(abs(t-3)<1e-12);
I3 = (q(k+1)-q(k-1))/(2*h);
fprintf('I(3) = %.5f A\n',I3);

%item b
fprintf('q(5) = %.5f C\n',q(end));

%cifras

[~,qRef] = dif_fin_rob(coef,intervalo,qInicial,robin,160);

error = abs(q(end)-qRef(end));

cifras = floor(-log10(2*error));

fprintf('Cifras exactas = %d\n',cifras);
