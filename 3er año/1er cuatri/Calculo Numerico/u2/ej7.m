% N=100 o sea matriz de N*N, 100*100

N=100;
A=zeros(N,N);
b=zeros(N,1);

A(1,1)=1; % Pongo un 1 en la posicion 1,1 ya que la consigna dice eso
A(N,N)=1; % Lo mismo para la pos N,N. Esto no es un valor sino que le estoy asignando un 1 a esa posicion
b(1)=0; % Segun la consigna esas posiciones valen cero
b(N)=0;

for i=2:N-1 % For que define matriz banda
  A(i,i-1)=-1;
  A(i,i)=2;
  A(i,i+1)=-1;
  b(i)=1/N^2;
endfor

x=gauss1(A,b)

% Graficar

t = linspace(0,1,N); % linspace genera N puntos desde 0 hasta 1

plot(t,x);
grid on;
xlabel('t');
ylabel('x(t)');
title('Solucion aproximada');





