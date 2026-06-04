
x=[0 1 2 3 4 5 6];

y=[432 599 1012 1909 2977 4190 5961];


% item a
p6=polyfit(x,y,6); %polinomio de grado 6 que interpola
y6=polyval(p6,x);

%polyfit y lagrange es lo mismo si tenes 4 datos y buscas el
%polinomio de grado 3 (lagranga siempre busca el polinomio de grado n-1
%ahora, si queres un polinomio de + o - grados, tenes q usar polyfit
%y ahi se diferencia de lagrange


% item b
%'que mejor aproxima en el sentido de cuadrados m´ınimos '
%-> minimizar error cuadratico (de esto se encarga polyfit)
p1= polyfit(x,y,1);
y1=polyval(p1,x);

% item c
p2=polyfit(x,y,2);
y2=polyval(p2,x);

% item d  graficar
xx=linspace(0,6,1000);

yy6=polyval(y6,xx);
yy1=polyval(y1,xx);
yy2=polyval(y2,xx);

figure

plot(x,y,'ko','markersize',8)
hold on

plot(xx,yy6,'b','linewidth',2)
plot(xx,yy1,'r','linewidth',2)
plot(xx,yy2,'g','linewidth',2)

grid on

legend('Datos','p6','p1','p2')
title('Comparación de modelos')

% error cuadratico
err_p6 = sum((y - polyval(p6,x)).^2);
disp('Error cuadratico en p6: '), disp(err_p6);
err_p1 = sum((y - polyval(p1,x)).^2);
disp('Error cuadratico en p1: '), disp(err_p1);
err_p2 = sum((y - polyval(p2,x)).^2);
disp('Error cuadratico en p2: '), disp(err_p2);
% el modelo que mejor se acerca es el de mayor orden


% item e predecir en semana 10
p6_10 = polyval(p6,10);
disp('Prediccion p6 en sem10: '), disp(p6_10);
p1_10 = polyval(p1,10);
disp('Prediccion p1 en sem10: '), disp(p1_10);
p2_10 = polyval(p2,10);
disp('Prediccion p2 en sem10: '), disp(p2_10);

% item f calcular error relativo
real=14900;

errR_p6= abs(real-p6_10)/real;
disp(' Error relativo con la prediccion de p6: '), disp(errR_p6);

errR_p1= abs(real-p1_10)/real;
disp(' Error relativo con la prediccion de p1: '), disp(errR_p1);

errR_p2= abs(real-p2_10)/real;
disp(' Error relativo con la prediccion de p2: '), disp(errR_p2);

% vemos que el mejor modelo para predecir(extrapolar) es el de orden 2






