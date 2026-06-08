%mala idea: L=1 y n=1000
%buena idea: n= 2 o 3 y L=4000


% Definición de funciones
f1 = @(x) sin(pi * x);
f2 = @(x) 1 ./ (1 + x.^2);
f3 = @(x) abs(x).^(3/2);

% Intervalos
a1 = 0;   b1 = 5;
a2 = -5;  b2 = 5;
a3 = 0;   b3 = 5;

% Integrales exactas
I1 = 2/pi;
I2 = atan(5)-atan(-5);
I3 = integral(f3,a3,b3);

% Valores de L y h
L_vals = 2.^(1:12); % 2 4 8 4096
%divido a,b en L pedazitos y en cada pedacito aplico un trapecio

h1 = (b1-a1)./L_vals;
h2 = (b2-a2)./L_vals;
h3 = (b3-a3)./L_vals;

% Inicializar errores
Etrap1 = zeros(size(L_vals)); Esimp1 = zeros(size(L_vals));
Etrap2 = zeros(size(L_vals)); Esimp2 = zeros(size(L_vals));
Etrap3 = zeros(size(L_vals)); Esimp3 = zeros(size(L_vals));

for i = 1:length(L_vals)

    L = L_vals(i);

    % Funcion 1
    Qtrap = intNCcompuesta(f1,a1,b1,L,2);
    Qsimp = intNCcompuesta(f1,a1,b1,L,3);

    Etrap1(i) = abs(I1-Qtrap);
    Esimp1(i) = abs(I1-Qsimp);

    % Funcion 2
    Qtrap = intNCcompuesta(f2,a2,b2,L,2);
    Qsimp = intNCcompuesta(f2,a2,b2,L,3);

    Etrap2(i) = abs(I2-Qtrap);
    Esimp2(i) = abs(I2-Qsimp);

    % Funcion 3
    Qtrap = intNCcompuesta(f3,a3,b3,L,2);
    Qsimp = intNCcompuesta(f3,a3,b3,L,3);

    Etrap3(i) = abs(I3-Qtrap);
    Esimp3(i) = abs(I3-Qsimp);

end

%% Tabla funcion 1

disp('--- f(x)=sin(pi*x) ---');
disp(' L       h          Etrap      E(L/2)/E(L)      Esimp      E(L/2)/E(L)');

for i = 1:length(L_vals)

    if i == 1
        fprintf('%4d  %.4e  %.4e      ----      %.4e      ----\n',...
        L_vals(i),h1(i),Etrap1(i),Esimp1(i));
    else
        fprintf('%4d  %.4e  %.4e   %.4f   %.4e   %.4f\n',...
        L_vals(i),h1(i),...
        Etrap1(i),Etrap1(i-1)/Etrap1(i),...
        Esimp1(i),Esimp1(i-1)/Esimp1(i));
    end

end

%% Tabla funcion 2

disp(' ');
disp('--- f(x)=1/(1+x^2) ---');
disp(' L       h          Etrap      E(L/2)/E(L)      Esimp      E(L/2)/E(L)');

for i = 1:length(L_vals)

    if i == 1
        fprintf('%4d  %.4e  %.4e      ----      %.4e      ----\n',...
        L_vals(i),h2(i),Etrap2(i),Esimp2(i));
    else
        fprintf('%4d  %.4e  %.4e   %.4f   %.4e   %.4f\n',...
        L_vals(i),h2(i),...
        Etrap2(i),Etrap2(i-1)/Etrap2(i),...
        Esimp2(i),Esimp2(i-1)/Esimp2(i));
    end

end

%% Tabla funcion 3

disp(' ');
disp('--- f(x)=|x|^(3/2) ---');
disp(' L       h          Etrap      E(L/2)/E(L)      Esimp      E(L/2)/E(L)');

for i = 1:length(L_vals)

    if i == 1
        fprintf('%4d  %.4e  %.4e      ----      %.4e      ----\n',...
        L_vals(i),h3(i),Etrap3(i),Esimp3(i));
    else
        fprintf('%4d  %.4e  %.4e   %.4f   %.4e   %.4f\n',...
        L_vals(i),h3(i),...
        Etrap3(i),Etrap3(i-1)/Etrap3(i),...
        Esimp3(i),Esimp3(i-1)/Esimp3(i));
    end

end
