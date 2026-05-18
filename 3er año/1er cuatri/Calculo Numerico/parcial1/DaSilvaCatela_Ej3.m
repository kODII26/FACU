addpath('../Funciones');

n = 100;

A = zeros(n,n);

i = (1:n)';
#y=mx+b
m=-8/99;
b = 4 + m .* (i - 1)';

% primer nodo
A(1,1)=4;
A(1,2)=-2;
A(1,4)=-1;

% nodos 2 a 10
for i=2:10
  A(i,i)=4;
  A(i,i+1)=-2;
  A(i,i+3)=-1;
endfor

% nodos 91 a 99
for i=91:99
  A(i,i)=4;
  A(i,i-1)=-2;
  A(i,i-3)=-1;
endfor

% nodos 11 a 90
for i=11:90
  A(i,i)=6;
  A(i,i+3)=-2;
  A(i,i-5)=-1;
  A(i,i+7)=-3;
endfor

% nodo borde derecho
A(100,100)=4;
A(100,99)=-2;
A(100,97)=-1;


x0=zeros(n,1);
tol=1e-5;
maxit=100000;
[x,it,r_h]=gauss_seidel(A,b,x0,maxit,tol);

9
fprintf('residuo iteracion 40 = %.10e\n',r_h(40));
fprintf('p1 = %.5f\n',x(1));
fprintf('p100 = %.5f\n',x(100));

