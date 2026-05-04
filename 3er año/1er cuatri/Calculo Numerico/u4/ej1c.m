f=@(x) x.^3+x-4;
tol=1e-3;
xmin=1;
xmax=4;
kmax=log2(abs(xmax-xmin)/tol);

[x, h] = biseccion(f, xmin, xmax, kmax, tol);
disp('El numero de iteraciones es');
disp(ceil(kmax)); %ceil redondea para arriba
disp('La raiz aproximada con el metodo de biseccion es'), disp(x);


