addpath('../Funciones');

x=[0 1 2 3 4 5 6];

y=[432 599 1012 1909 2977 4190 5961];

%error cuadratico del ajuste
p4=polyfit(x,y,4);
y4=polyval(p4,x);

err_p4= sum((y-y4).^2);
printf('%.6g\n',err_p4);

%error relativo a las 10 sem
y_real=14900;

p4_10=polyval(p4,10);

err_Rel= abs(p4_10-y_real)/y_real;

printf('%.6g\n',err_Rel);
