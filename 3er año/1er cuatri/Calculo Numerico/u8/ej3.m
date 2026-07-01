addpath('../Funciones');

a = 1;
b = 2;
alpha = 1;
beta  = 2;
% Definicion de p,q,r
f = @(x) [ -2./x , 2./x.^2 , sin(log(x))./x.^2 ];

% Solucion exacta
c2 = (8 - 12*sin(log(2)) - 4*cos(log(2)))/70;
c1 = 11/10 - c2;

yex = @(x) c1*x + c2./x.^2 -3/10*sin(log(x)) -1/10*cos(log(x));

% h = 0.1
L = 10;
[x1,y1] = dif_fin_dir(f,[a b],[alpha beta],L);
ye1 = yex(x1);
error1 = max(abs(y1-ye1));

fprintf('h = 0.1\n');
fprintf('Error maximo = %.10e\n\n',error1);

% h = 0.01
L = 100;
[x2,y2] = dif_fin_dir(f,[a b],[alpha beta],L);
ye2 = yex(x2);
error2 = max(abs(y2-ye2));

fprintf('h = 0.01\n');
fprintf('Error maximo = %.10e\n\n',error2);

% Orden empiric
orden = log(error1/error2)/log(10);

fprintf('Orden empirico = %.6f\n',orden);

% Graficos
figure(1)
plot(x2,ye2,'k','linewidth',2)
hold on
plot(x2,y2,'ro')
grid on
legend('Exacta','Disparo')
title('Metodo del disparo lineal')
