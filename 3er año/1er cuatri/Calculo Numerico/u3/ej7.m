% armar la matriz sin for:
% S=diag(v,k) . v: vector de valroes, k: en que diagonal insertar
% r_h= historial del residuo/error por iteración

n=1000;
A= zeros(n,n) + diag(2*[1:n],0) + diag(0.5*[1:n-2],2) + diag(0.5*[3:n],-2) + diag(0.25*[1:n-4],4) + diag(0.25*[5:n],-4);
b=pi*ones(n,1);
x0=zeros(n,1);
tol= 1e-5;
maxit=1000;
w=1;

% JACOBI
[x_j,it_j,r_h_j,t_j]= jacobi(A,b,x0,maxit,tol);
disp('METODO JACOBI:');
disp('TIEMPO DE EJECUCION: ');
disp(t_j);
disp('NUMERO ITERACIONES: ');
disp(it_j);

% GAUSS SEIDEL
[x_gs,it_gs,r_h_gs,t_gs]= gauss_seidel(A,b,x0,maxit,tol);
disp('METODO GAUS SEIDEL:');
disp('TIEMPO DE EJECUCION: ');
disp(t_gs);
disp('NUMERO ITERACIONES: ');
disp(it_gs);

% SOR
[x_s,it_s,r_h_s,t_s]= sor(A,b,x0,maxit,tol,w);
disp('METODO SOR:');
disp('TIEMPO DE EJECUCION: ');
disp(t_s);
disp('NUMERO ITERACIONES: ');
disp(it_s);

% GRAFICOS
figure(1)
semilogy(1:length(r_h_j), r_h_j, 'b-o')
grid on
xlabel('Numero de iteraciones')
ylabel('Norma del residuo')
title('Jacobi')

figure(2)
semilogy(1:length(r_h_gs), r_h_gs, 'r-s')
grid on
xlabel('Numero de iteraciones')
ylabel('Norma del residuo')
title('Gauss-Seidel')

figure(3)
semilogy(1:length(r_h_s), r_h_s, 'k-^')
grid on
xlabel('Numero de iteraciones')
ylabel('Norma del residuo')
title('SOR')



