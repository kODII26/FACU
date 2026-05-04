clear;
tol=1e-5;
kmax=100;
f = @(t) ((t+1/3).^3+1/3).*exp(-t);

%grafico para  ver intervalos de raices y de 1.5
tv=linspace(0,5,100);
plot(tv,f(tv)); title('Funcion');


%          inciso 1;
f1 = @(t) ((t+1/3).^3+1/3).*exp(-t)-1.5;
%Lo resuelvo por newton asi que necesito la derivada
df = @(t) (3*(t+1/3).^2).*exp(-t) - ((t+1/3).^3+1/3).*exp(-t);
%primer cruce
x0=1.4;
[x_1, h_1] = newton(f1, df, x0, kmax, tol);
disp('Vale 1.5 en: '), disp(x_1);
disp('Cantidad de iteraciones: '), disp(length(h_1)-1);
% segundo cruce
x0=4;
[x_1, h_1] = newton(f1, df, x0, kmax, tol);
disp('Vale 1.5 en: '), disp(x_1);
disp('Cantidad de iteraciones: '), disp(length(h_1)-1);


%         inciso 2;
%para maximizar, derivo e igualo a cero, la derivada ya la tengo del inciso 1
% si quisiese resolver por newton tengo que derivar devuelta, por lo tanto usare secante
%grafico la df para ver donde aproximadamente encuentra el maximo
figure;
plot(tv,df(tv)); title('Derivada');

xmin=2;
xmax=3; %agarro el segundo cruce por cero, para el maximo y no el minimo
[x_2, h_2] = secante(df, xmin, xmax, kmax, tol);
disp('Resultado inciso 2: '), disp(x_2);
disp('Cantidad de iteraciones: '), disp(length(h_2)-1);
disp('La maxima energia es '), disp(f(x_2));

%         inciso 3
%tasa de crecimiento es la primer derivada, y como me pide el maximo
% necesito hallar la 2da derivada
figure;

ddf = @(t) (6*(t+1/3).^1).*exp(-t) - (6*(t+1/3).^2).*exp(-t) + ((t+1/3).^3+1/3).*exp(-t);
plot(tv,ddf(tv)); title('2Da derivdada');
%vemos que la 2da derivada cruza cerca de 1
xmin=0;
xmax=1;
[x_3, h_3] = secante(ddf, xmin, xmax, kmax, tol);
disp('Resultado inciso 3: '), disp(x_3);
disp('Cantidad de iteraciones: '), disp(length(h_3)-1);





