A = [ 3   1  -1   1   2;
      1   3   2  -2  -2;
     -2  -2   1  -2  -2;
      2  -1  -1   3   2;
      0   0   1   1   2 ];

b = [ 1 4 -1 2 2]';

x=gauss1(A,b);

fprintf('x1 = %.3f\n', x(1))
fprintf('x2 = %.3f\n', x(2))
fprintf('x3 = %.3f\n', x(3))
fprintf('x4 = %.3f\n', x(4))
fprintf('x5 = %.3f\n', x(5))


% parte 2
x0=zeros(length(b),1);
maxit=10000;
tol=1e-4;
[x_j,it_j,r_h_j]=jacobi(A,b,x0,maxit,tol);
disp('Iteraciones jacobi: '), disp(it_j);

[x_gs,it_gs,r_h_gs]=gauss_seidel(A,b,x0,maxit,tol);
disp('Iteraciones gauss seidel: '), disp(it_gs);

err_rel = norm(x_j - x, inf) / norm(x, inf)






