addpath('../Funciones');

x=[-1 1 2 3 4]';
y=[0.23 0.25 0.26 0.14 0.06]';

%  y= a/(be^x+cx+7.5)
%  1/y= (be^x+cx+7.5)/a
%  1/y= be^x/a + cx/a + 7.5/a
% renombro:
% Y=1/y , A= b/a , B= c/a , C=7.5/a
% me queda entonces
% Y= A.e^x + B.x + C
% y armo la matriz con eso
Y=1./y;

A= [exp(x) x ones(length(x),1)];

coef= A\Y;
A=coef(1);
B=coef(2);
C=coef(3);
%ahora reemplazo para obtener a,b,c
a=7.5/C;
c=a*B;
b=A*a;
disp('coeficientes: ');
fprintf('a = %.7g\n',a);
fprintf('b = %.7g\n',b);
fprintf('c = %.7g\n',c);

%item b
[a_spline, b_spline, c_spline, d_spline] = cubic_spline_natural(x', y');
%los paso traspuestos para que se manden como filas
% ya que cubic spline trabaja con vectores filas no columna
val = spline_eval(0, x, a_spline, b_spline, c_spline, d_spline);
disp('val del spline en x=0: ');
fprintf('y = %.7g\n',val);

%item c
val_real=0.23;

%error del modelo a:
%primero hallo la aprox para x=0 ya que no la tengo
x0=0;
aprox_a= a/(b*exp(x0) + c*x0 +7.5);

%ahora si calculo los errores rel
errRel_a= abs(val_real-aprox_a)/val_real;

errRel_b= abs(val_real-val)/val_real;
fprintf('error por minimos cuadrados = %.4g\n',errRel_a);
fprintf('error por spline cubico = %.4g\n',errRel_b);


