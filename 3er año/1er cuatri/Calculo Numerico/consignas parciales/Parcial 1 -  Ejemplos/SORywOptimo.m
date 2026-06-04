%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% como usar el Método SOR y obtener el w optimo
%[TSOR, cSOR, tSOR]=Tc_SOR(A, b, w);

maxitSOR=500;
[rhoSOR pos]=max(abs(eig(-inv(D+w*L)*((w-1)*D+w*U))));
disp('radio Spectral Matriz Iteracion SOR')
rhoSOR

wsor=linspace(1.7,2,30);
% calculamos el radio espectral de la matriz de iteracion de Gauss-Seidel
vit=[];

for j=1:length(wsor)

[xSOR, rSOR, itSOR, tSOR] =sor(A, b, x0, maxitSOR, tol, wsor(j));
vit(j)=itSOR;

end

% calculo con el minimo wsor
figure(1)
plot(wsor,vit,'-or')
grid on
grid minor
title('Grafica wsor vs Nro Iteraciones')

dato=[wsor; vit]';
[val pos]=min(dato(:,2));
wsor_min=wsor(pos)

[rhoSOR pos]=max(abs(eig(-inv(D+wsor_min*L)*((wsor_min-1)*D+wsor_min*U))));
disp('radio Spectral Matriz Iteracion SOR')
rhoSOR

[xSOR_min,rSOR_min,itSOR_min,tSOR_min] =sor(A, b, x0, maxitSOR, tol, wsor_min);

figure(2)
semilogy(rJ,'-*b')
grid on
grid minor
hold on
semilogy(rGS,'-or')
semilogy(rSOR_min,'-+g')
title('Grafica de convergencia de cada Metodo')
hold off

figure(3)
semilogy(rSOR_min,'-+g')
grid on
grid minor

figure(4)
plot(z,xJ,'-ob',z,xGS,'-*r',z,xSOR_min,'-+g')
grid on
grid minor
title('Solucion del sistema')