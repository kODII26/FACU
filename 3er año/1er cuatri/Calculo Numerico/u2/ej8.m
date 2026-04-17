
A1=[8 4 1; 2 6 2; 2 4 8];
A2=[5.00e-02   5.57e+02  -4.00e-02;
    1.98e+00   1.94e+02  -3.00e-03;
    2.74e+02   3.11e+00   7.50e-02];
A3=[1 2 -1; 2 4 0; 0 1 -1];
b=[1 2 3]';

% Calculo A1 sin pivoteo
Af=doolittle(A1);
[L,U] = extraer_LU(Af);

y= sust_adelante(L,b); % Solucion intermedia
x=sust_atras_vec(U,y); % Solucion final
r = b - A1*x;

printf("A1 sin pivoteo:\n");
disp("x = "), disp(x)

printf("Residuo A1:\n"); disp(r)

%Conclusion residuos: da 0 y un numero muy cercano al cero entonces la solucion obtenida es buena

% Calculo A2 con pivoteo:

[Af,r] = doolittle_p(A2);
PAf= Af(r,:);

[L,U]= extraer_LU(PAf);
bp=b(r);
y=sust_adelante(L,bp);
x=sust_atras_vec(U,y);

printf("A2 con pivoteo:\n");
disp("x = "), disp(x)

% Verificar resultado A2*x
printf("verificacion, tiene que dar 1 2 3 como el vector b\n");
A2*x
