addpath('../Funciones');

%item a

g = 9.8;
c = 15;
t = 9;
v = 30;

f = @(m) c.*v-g.*m.*(1-exp(-c.*t./m));
df = @(m) -g.*(1-exp(-c.*t./m)) -g.*(c.*t./m).*exp(-c.*t./m);

[x,h] = newton(f,df,100,10000,1e-5);
fprintf('masa que deberia tener el paracaidista = %.3f\n', x)

% item b

m = 54;

f = @(c) c.*v - g.*m.*(1-exp(-c.*t./m));

df = @(c) v - g.*t.*exp(-c.*t./m);

[xc,hc] = newton(f,df,15,10000,1e-5);

fprintf('Coeficiente c = %.3f kg/s\n',xc);



