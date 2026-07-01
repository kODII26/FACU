addpath('../../Funciones');

p=@(x) (2.*x)./(1-x.^2);
q=@(x) -42./(1-x.^2);
r=@(x) 0*x;
f=@(x) [p(x) q(x) r(x)];


inter=[-1 1];
yc=[1 1];
L=100;
for i=1:10
    [xdf,ydf]=dif_fin_dir(f,inter,yc,L);
    index = find(xdf==0);
    y0 = ydf(index);
    fprintf("y(0) = %.6f\n",y0);
    L=L*2;
endfor



%esto esta mal pq calcula y'(-1), nada q ver
%h=xdf(2)-xdf(1);
%y0=(ydf(2)-ydf(1))/h;
%aca si

%item b
coef = polyfit(xdf, ydf, 6);
a = fliplr(coef);      % ahora a(1)=a0, ..., a(7)=a6
fprintf("\na0 = %.3f\n",a(1));
fprintf("a1 = %.3f\n",a(2));
fprintf("a2 = %.3f\n",a(3));
fprintf("a3 = %.3f\n",a(4));
fprintf("a4 = %.3f\n",a(5));
fprintf("a5 = %.3f\n",a(6));
fprintf("a6 = %.3f\n",a(7));

%item c
raices = roots(coef);

% quedarse solo con las reales
raices = raices(abs(imag(raices)) < 1e-10);

% quedarse solo con las positivas
raices = raices(raices > 0);

% ordenarlas de menor a mayor
raices = sort(raices);

fprintf("\nRaiz menor = %.8f\n",raices(1));
fprintf("Raiz del medio = %.8f\n",raices(2));
fprintf("Raiz mayor = %.8f\n",raices(3));

