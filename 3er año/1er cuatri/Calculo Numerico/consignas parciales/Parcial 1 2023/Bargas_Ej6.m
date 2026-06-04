disp("EJERCICIO 6")
f_6 =@(x) sin(x) + (cos(1+x.^2)) - 1;
df_6 = @(x) cos(x) - 2*x.*sin(1 + x.^2);

format long;

figure(1)
m6=linspace(7,9,1000);
plot(m6,f_6(m6));

tol6=1e-10;
x0=8;
[x6,rh6,it6,t6] = NewtonRaphson(f_6,df_6,x0,1000,tol6);
disp("El valor mas cercano es ")
x6

printf("%.10f", x6)
