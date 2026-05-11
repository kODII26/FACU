addpath('../Funciones');

t= [0 , 0.0025 , 0.005 , 0.0075 , 0.01]';
b=[2.1004, 4.3702 , 5.1745 , -0.7222 , 0.9249]';
f= [440, 660, 1100, 5, 8];

A=zeros(5,5);

A(:,1)= sin(2*pi*f(1)*t);
A(:,2)= sin(2*pi*f(2)*t);
A(:,3)= sin(2*pi*f(3)*t);
A(:,4)= cos(2*pi*f(4)*t);
A(:,5)= sin(2*pi*f(5)*t);

[a,r] = gauss_p(A,b);
fprintf('A1 = %.4f\n', a(1))
fprintf('A2 = %.4f\n', a(2))
fprintf('A3 = %.4f\n', a(3))
fprintf('A4 = %.4f\n', a(4))
fprintf('A5 = %.4f\n', a(5))

tol=1e-4;
maxit=1000;

% item b; hallar w opt y aplicar SOR
% primero debo hallar la matriz de iteracion de jacobi Tj
% luego calculo el max autovalor de Tj y hallo w en base a eso

Ap=A(r,:);

%Matriz iteracion jacobi Tj=-D^-1*(L+U)
D=diag(diag(Ap));
L=tril(Ap,-1);
U=triu(Ap,1);

Tj= -D\(L+U); % o tambien: -inv(D)*(L+U)

%SOR: calcular w optimo
[V,De]= eig(Tj); %En V estan los autovectores y en D una matriz con autovalores
autovalores= diag(De);
rho = max(abs(autovalores));
Wopt= 2/(1+sqrt(1-rho^2));

%El woptimo calculado da un valor imaginario por lo tanto determinamos que p(Tj)>1
% entonces jacobi no converge para la matriz permutada
% y procedemos a hacer un barrido para encontrar el mejor w.


wvals = 0.1:0.1:1.9;

best_it = inf;
wopt = 0;

x0 = zeros(length(b),1);

for w = wvals

    [x,it,r_h] = sor(Ap,b(r),x0,10000,1e-4,w);

    if(it < best_it)

        best_it = it;
        wopt = w;

    endif

endfor

disp(wopt)
disp(best_it)




