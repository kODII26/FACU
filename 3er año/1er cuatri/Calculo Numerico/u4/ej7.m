clear;
f= @(x) x.*(log(x+3)-17)-1;
a=0;
b=1;
while (f(a)*f(b)>0)
  b*=2;
endwhile
kmax=100;
%aproximo con biseccion
tol1=1e2;
[x_b, h_b] = biseccion(f, a, b, kmax, tol1);
disp('Solucion con biseccion: '), disp(x_b);
disp(['Cantidad de iteraciones: ', num2str(length(h_b) - 1)]);

tol2=1e-12;
df = @(x) (log(x+3)-17) + x./(x+3);
[x, h] = newton(f, df, x_b, kmax, tol2);
disp('Solucion con newton: '), disp(x);
disp(['Cantidad de iteraciones: ', num2str(length(h) - 1)]);

