xmin=-2;
xmax=1.5;
kmax=4;
tol=1e-5;

f = @(x) 3.*(x+1).*(x-0.5).*(x-1);

[x, h] = biseccion(f, xmin, xmax, kmax, tol);
disp('el valor aproximado de x es: ');
disp(x);
disp('el historial de aproximaciones es: ')
disp(h);


#ahora para hallar la cota del error lo que hago es hacerla por def.
#cota=b-a/2^n donde b es el extremo superior del intervalo y a el inferior. n la cant de iteraciones.
cota=(xmax-(xmin))/(2^kmax);
disp('la cota del error hallada es: ');
disp(cota);
