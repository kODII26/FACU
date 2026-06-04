% medicion cada 12 minutos durante 5 horas
% son 26 mediciones en total 5*5+1
% 12min = 0.2h

v = load('datos_velocidades.txt');
t = 0:0.2:5;
% Inciso (a)
% Ajuste:
% v(t)=c1*sin(2t)+c2*t^2+c3*2^t+c4
A = [sin(2*t') (t'.^2) (2.^t') ones(length(t),1)];
%no es una matriz de vandermonde ya que las columnas no son
%potencias consecutivas

c = A\v; %no puedo usar gaussLUP ya que espera
%matriz cuadrada y aca la matriz es de 26x4

c1 = c(1);
c2 = c(2);
c3 = c(3);
c4 = c(4);

fprintf('c1 = %.4f\n',c1);
fprintf('c2 = %.4f\n',c2);
fprintf('c3 = %.4f\n',c3);
fprintf('c4 = %.4f\n',c4);

%Prediccion a las 6 horas

v6_modelo = c1*sin(12) + c2*6^2 + c3*2^6 + c4;

fprintf('\nVelocidad a las 6 hs (modelo a):\n');
fprintf('%.4f km/h\n',v6_modelo);


%% Inciso (b) Ajuste polinomico grado 6
p6 = polyfit(t,v,6);

v6_p6 = polyval(p6,6); %escalar

fprintf('\nVelocidad a las 6 hs (p6):\n');
fprintf('%.4f km/h\n',v6_p6);


%% Inciso (c) Error cuadratico
v_aprox_a = c1*sin(2*t) + c2*t.^2 + c3*2.^t + c4;

v_aprox_p6 = polyval(p6,t); %vector

err_a = sum((v - v_aprox_a).^2);

err_p6 = sum((v - v_aprox_p6).^2);

fprintf('\nError cuadratico modelo (a): %.6f\n',err_a);
fprintf('Error cuadratico p6: %.6f\n',err_p6);

%Graficos
tt = linspace(0,6,1000);

vv_a = c1*sin(2*tt) + c2*tt.^2 + c3*2.^tt + c4;

vv_p6 = polyval(p6,tt);

figure

plot(t,v,'ko','markersize',6)
hold on

plot(tt,vv_a,'b','linewidth',2)

plot(tt,vv_p6,'r','linewidth',2)

grid on

legend('Datos','Modelo (a)','p6')

xlabel('t (hs)')
ylabel('v (km/h)')

title('Ajustes por minimos cuadrados')


%% Inciso (d) Distancia recorrida usando el modelo elegido

% Elegimos el modelo (a)

tt = linspace(0,6,1000);

vv = c1*sin(2*tt) + c2*tt.^2 + c3*2.^tt + c4;

h = tt(2)-tt(1);

dist = h*( sum(vv) - (vv(1)+vv(end))/2 );

fprintf('\nDistancia recorrida en 6 hs:\n');
fprintf('%.4f km\n',dist);
