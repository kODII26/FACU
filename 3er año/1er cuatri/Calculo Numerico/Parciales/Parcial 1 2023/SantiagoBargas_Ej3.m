clc
clear
%la segunda derivada nos da la tasa de maximo incremento o decrecimiento
%INCOGNITA U
%[2 1 0 0 . . . ] * [ U ] = [5]

%h es la distancia entre dos puntos
%h=sqrt( (x(i+1)-x(i)).^2 + (y(j+1) - y(j)).^2 )

%CREAMOS LA MATRIZ

n=39 ;
function [A,b]= MatrizParcial(n)
  x=linspace(0,1,41);  %distancia de un punto para h
  h=x(2);  %evaluo h en la distancia
  A=zeros(n,n); %creo la matriz de 39x39 con ceros
  b=ones(n,1); %creo el vector solucion con 39 1s
  u0=5; %defino u0 y u1
  u1=6;
    for i=1:n
      b(i)= (h^2)*20*e^(-10(x(i)-0.07)^2); %defino b(i) para el vector solucion
   endfor
    b(1)=((h.^2)*20*e^(-10(h-0.07)^2))+u0; %b1 le sumo u0
    b(n)=((h.^2)*20*e^(-10(1-h-0.7)^2))+u1; %b39 le sumo u1
   for j=2:n
        A(j-1,j)=-1; %-1 arriba
         A(j,j)=2; %dos en la diagonal
         A(j+1,j)=-1; %-1 abajo
      endfor
     A(1,1)= 2;
     A(2,1)= -1;
     A(1,n)=-1;
     A(1,n)=2;





%definimos la tolerancia
tol=1e-6;

%vector inicial x0
x0=zeros(n,1);

[A,b]=MatrizParcial(39)
[xGauss, rGauss, itGauss, tGauss] = GaussSeidel(A, b, x0, 1000, tol);
disp("La cantidad de iteraciones necesarias son:")
itGauss





