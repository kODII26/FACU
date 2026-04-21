A= [10 5 0 0; 5 10 -4 0; 0 -4 8 -1; 0 0 -1 5];

b=[6 25 -11 -11]';

[V,D] = eig(A);
autovalores= diag(D);


%Los autovalores son positivos y la matriz es simetrica por lo tanto
%SOR converje para todo w en (0,2)

x0 = zeros(length(b),1);
maxit = 1000;
tol = 1e-8;
w=1;
[x, it,r_h] = sor(A,b,x0,maxit,tol,w);
disp(x);
