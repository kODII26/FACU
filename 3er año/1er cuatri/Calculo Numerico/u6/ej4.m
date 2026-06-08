
%defino las funciones
f1= @(x) sin(pi.*x);
f2= @(x) 1./(1+x.^2);

%integrales evaluadas en los extremos
I1= 2/pi;
I2= atan(5)-atan(-5);

disp('Tabla de f(x)=sen(pi*x) en [0,5] ');
xx = linspace(0,5,1000);

for n=2:13

    x = linspace(0,5,n);
    y = f1(x);

    p = polyfit(x,y,n-1);

    yy = polyval(p,xx);

    figure
    plot(xx,f1(xx),'LineWidth',2)
    hold on
    plot(xx,yy,'LineWidth',2)
    plot(x,y,'o')
    grid on

    title(sprintf('sin(pi*x) - n=%d',n))
    legend('f(x)','Interpolante','Nodos')

end

disp('Tabla de f(x)=1/1+x^2 en [-5,5] ');
for n=2:13
  Q = intNCcompuesta(f2,-5,5,1,n);
  err= abs(I2-Q);
  fprintf('n=%2d   Error=%e\n',n,err);
end

%item b


