clear all;clc
%Ejercicio 3 Antuna Bianchi, Brisa
  #[A b] = crearSistema(39);

  b = zeros(39,1);
  %A = zeros(39,39);
  h = 1/40;
  A(1,1) = 2;
  A(1,2) = -1;
  A(39,38) = -1;
  A(39,39) = 2;
   b(1) = h^2*20*e^(-10*(h-0.7)^2)+5;
   b(39) = h^2*20*e^(-10*(1-h-0.7)^2)+6;
  for i = 2:38
    b(i) = h^2*20*e^(-10*((h*i)-0.7)^2);
    A(i,i-1) = -1;
    A(i,i) = 2;
    A(i,i+1) = -1;
  endfor

  tolerancia = 10^(-6);
  xini = zeros(39,1);
  kmax = 2000;
  [x, it, resto] = GaussSeidel(A,b,xini,tolerancia,kmax);
  x;
  it
  x(20)


