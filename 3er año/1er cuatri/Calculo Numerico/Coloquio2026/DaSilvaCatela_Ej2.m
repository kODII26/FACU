
addpath('../Funciones')

F = @(t,y) [-0.013*y(1)-1000*y(1)*y(3);
-2500*y(2)*y(3);
0.013*y(1)-2500*y(2)*y(3)-1000*y(1)*y(3)];

t0 = 0;
tf = 50;

N = 100000;

y0 = [1;1;0];

[t,y] = rk4(F,[t0 tf],y0,N);

cA = y(:,1);
cB = y(:,2);

fprintf('cA(50)= %.4f\n',cA(end));
fprintf('cB(50)= %.4f\n',cB(end));

AUC = trapcomp(t,cB);

fprintf('AUCB = %.4f\n',AUC);
