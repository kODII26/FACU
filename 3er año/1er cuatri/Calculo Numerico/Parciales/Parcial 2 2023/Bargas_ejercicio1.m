clc;
clear all;

x=[0.0 0.2 0.4 0.6 0.8 1.0 1.2 1.4 1.6 1.8 2.0];
y=[4.16 4.43 4.87 5.45 5.59 5.20 3.78 2.12 0.26 -1.26 1.95];

%f=a0 + a1*cos( (pi*x)/2) + a2*cos^2*( (pi*x)/2)


%podemos hacer un cambio de variable con z= cos( (pi*x)/2) y volvemos a z;
%z=@(z) a0 + (a1*z) + (a2*z^2)
z=(cos((pi*x)/2));

[coef,A,b] = minimoscuadrados(z,y,2);
a0=coef(3);
a1=coef(2);
a2=coef(1);

%reemplazamos z en la funcion principal con los coef ya calculados
f=@(x) a0 + (a1.*cos((pi.*x)./2)) + (a2.*(cos((pi.*x)./2)).^2)

%el punto donde debemos ver el error es x=1
xerror=1;

error=abs(f(xerror)-5.20); %calculamos el error como el valor abs de la resta de la funcion evaluada en el punto - el valor real de x=1 en la tabla

disp("Los valores son")
disp("a0:");a0
disp("a1:");a1
disp("a2:");a2

disp("El error es: ")
error


