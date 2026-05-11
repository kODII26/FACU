addpath('../Funciones');

A = [ 2   1   0  -2   1;
      2   2   1   2  -1;
     -2  -2   2   1   0;
     -1   1   1   2   1;
     -2   2  -2   0   3 ];

b = [ 2;
      0;
      6;
      7;
      3 ];

      % item b
x= gauss1(A,b);
fprintf('x1 = %.3f\n', x(1))
fprintf('x2 = %.3f\n', x(2))
fprintf('x3 = %.3f\n', x(3))
fprintf('x4 = %.3f\n', x(4))
fprintf('x5 = %.3f\n', x(5))


tol=1e-4;
x0=zeros(length(b),1);
maxit=10000;
[x_j,it_j,r_h_j]=jacobi(A,b,x0,maxit,tol);
disp('Iteraciones con jacobi: '), disp(it_j);
[x_gs,it_gs,r_h_gs]=gauss_seidel(A,b,x0,maxit,tol);
disp('Iteraciones con gs: '), disp(it_gs);

% item c
err_rel = norm(x_j - x, inf) / norm(x, inf);
fprintf('error relativo = %.7f\n', err_rel)









