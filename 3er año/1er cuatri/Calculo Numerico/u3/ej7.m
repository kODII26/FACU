% armar la matriz sin for:
% S=diag(v,k) . v: vector de valroes, k: en que diagonal insertar

n=1000;
A= zeros(n,n) + diag(2*[1:n],0) + diag(0.5*[1:n-2],2) + diag(0.5*[3:n],-2) + diag(0.25*[1:n-4],4) + diag(0.25*[5:n],-4);
b=pi*ones(n,1);
tol= 1e-5;
maxit=1000;


