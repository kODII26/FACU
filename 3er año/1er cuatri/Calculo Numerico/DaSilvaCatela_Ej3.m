addpath('Funciones');

%16x^2+4y^2=64
%divido por 64
%1/4x^2 + 1/16y^2 = 1
%a=2 y b=4

%parametrizacion de la elipse
a = 2;
b = 4;

%la elipse parametrizada queda:
%a(t)= 2cos(t) + 4sin(t)
%le calculo la derivada
%a'(t)= -2sin(t) + 4cos(t)

df = @(t) sqrt( (-a*sin(t)).^2 + (b*cos(t)).^2 );

%item a
L=1;
for i=1:10
    I = cuad_gauss_c(df,0,2*pi,L,2);
    disp('L: '),disp(L);
    printf("%.14f\n",I);
    L=L*2;
endfor

fprintf('longitud con 10 cifras exactas= %.10g\n',L_real);

%item b

Q = cuad_gauss_c(df,0,2*pi,3,2);

fprintf('gauss compuesta 3 subintervalos = %.10g\n',Q);

Q2 = cuad_gauss_c(df,0,2*pi,6,2);

fprintf('gauss compuesta 6 subintervalos = %.10g\n',Q2);

Q3 = cuad_gauss_c(df,0,2*pi,12,2);

fprintf('gauss compuesta 12 subintervalos = %.10g\n',Q3);

%tengo 3 cifras exactas: 19,3
