
a=0.401;
b=42.7e-6;
N=1000;
T=300;
p=3.5e7;
tol=1e-12;
k=1.3806503e-23;
kmax=100;


f=@(V) (p+a.*(N./V).^2).*(V-N.*b)-k.*N.*T;
df = @(V) p - a.*(N./V).^2 + 2.*a.*b.*(N.^3 ./ V.^3);

% grafico para obtener los intervalos
xv=linspace(0,1,100);
plot(xv,f(xv));
% vemos que la raiz esta en x=0.04 aproximadamente
x0=0.04;
[x_n, h_n] = newton(f, df, x0, kmax, tol);
disp('Resultado con newton '), disp(x_n);
disp(['Cantidad de iteraciones: ', num2str(length(h_n) - 1)]);


% ahora lo hago con biseccion
xmin=0.02;
xmax=0.06;
[x_b, h_b] = biseccion(f, xmin, xmax, kmax, tol);
disp('Resultado con biseccion '), disp(x_b);
disp(['Cantidad de iteraciones: ', num2str(length(h_b) - 1)]);





