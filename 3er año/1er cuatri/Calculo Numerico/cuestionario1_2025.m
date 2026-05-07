
n=40;
A= zeros(n,n)+diag(2*ones(n,1),0) + diag(-1*ones(n-1,1),1) + diag(-1*ones(n-1,1),-1);

i=(1:n)';
b=1.5*i-6;

x= gauss1(A,b);
x(20);

x0=zeros(n,1);
maxit=10000;
tol=1e-5;

[x_j,it_j,r_h_j,t_j]=jacobi(A,b,x0,maxit,tol);
disp('Iteraciones jacobi'), disp(it_j);

[x_gs,it_gs,r_h_gs,t_gs]=gauss_seidel(A,b,x0,maxit,tol);
disp('Iteraciones gs'), disp(it_gs);

w=1.85;
[x_sor,it_sor,r_h_sor,t_sor]=sor(A,b,x0,maxit,tol,w);
disp('Iteraciones sor'), disp(it_sor);


% Prueba: calcular matrices de iteracion y w optimo en SOR

%Matriz iteracion jacobi Tj=-D^-1*(L+U)
D=diag(diag(A));
L=tril(A,-1);
U=triu(A,1);

Tj= -D\(L+U); % o tambien: -inv(D)*(L+U)

%Matriz iteracion gauss seidel Tgs=-(D+L)^-1*U
D=diag(diag(A));
L=tril(A,-1);
U=triu(A,1);

Tgs= -(D+L)\U;

%SOR: 1ero calcular w optimo, luego matriz Tw
[V,De]= eig(Tj); %En V estan los autovectores y en D un vector con autovalores
autovalores= diag(De);
rho = max(abs(autovalores));
Wopt= 2/(1+sqrt(1-rho^2))

%Ahora con woptimo puedo calcular Tw=(D+wL)^-1*[(1-w)D-wU]
D=diag(diag(A));
L=tril(A,-1);
U=triu(A,1);

Tw= inv(D+w*L)*((1-w)*D-w*U)










