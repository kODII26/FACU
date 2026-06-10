
f = @(t,y) t.*exp(3*t) - 2*y;

dfdy = @(t,y) -2;

yexacta = @(t) (t.*exp(3*t))/5 - exp(3*t)/25 + exp(-2*t)/25;

hvec = [0.2 0.1 0.05];

errE = zeros(size(hvec));
errEA = zeros(size(hvec));
errCN = zeros(size(hvec));

for i=1:length(hvec)

    h = hvec(i);

    N = round(1/h);

    [tE,yE] = euler(f,[0 1],0,N);

    [tEA,yEA] = euler_atras(f,dfdy,0,1,0,N);

    [tCN,yCN] = CN_newton(f,dfdy,0,1,0,N);

    yex = yexacta(1); %para ver el error al final de la integracion

    errE(i)  = abs(yex-yE(end));
    errEA(i) = abs(yex-yEA(end));
    errCN(i) = abs(yex-yCN(end));

end

disp(' ');
disp('        h           Euler         Euler atras      Crank-Nicholson');

for i=1:length(hvec)

    fprintf('%8.3f   %12.4e   %12.4e   %12.4e\n',...
            hvec(i),errE(i),errEA(i),errCN(i));

end

disp(' ');
disp('Orden empirico');

pE1  = log2(errE(1)/errE(2));
pE2  = log2(errE(2)/errE(3));

pEA1 = log2(errEA(1)/errEA(2));
pEA2 = log2(errEA(2)/errEA(3));

pCN1 = log2(errCN(1)/errCN(2));
pCN2 = log2(errCN(2)/errCN(3));

fprintf('\nEuler:\n');
fprintf('h=0.2 -> 0.1 : %.4f\n',pE1);
fprintf('h=0.1 -> 0.05: %.4f\n',pE2);

fprintf('\nEuler atras:\n');
fprintf('h=0.2 -> 0.1 : %.4f\n',pEA1);
fprintf('h=0.1 -> 0.05: %.4f\n',pEA2);

fprintf('\nCrank-Nicholson:\n');
fprintf('h=0.2 -> 0.1 : %.4f\n',pCN1);
fprintf('h=0.1 -> 0.05: %.4f\n',pCN2);


%En general, para pasos suficientemente pequeños, los métodos de mayor orden
%presentan menores errores globales. Sin embargo, el error también depende de las
%constantes asociadas al problema, por lo que un método de mayor orden no necesariamente
% será más preciso para cualquier valor de h.
