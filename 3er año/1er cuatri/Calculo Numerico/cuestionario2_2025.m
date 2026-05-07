format long;
addpath('Funciones');
tol=1e-6;
kmax=100;

% Como dice que tiene punto fijo en t=0.02,  entonces
% z(0.02)=0.02
% Viendo las similitudes de z y w es logico pensar que a tiene que estar cerca de 19
% (No vale 19 exacto ya que dice que pasa cerca)
% Luego reemplazo 0.02 en z y dejo en funcion de a, formando esto:
z= @(a) 0.0392.*(a+0.02).^0.5-0.02.*(3.*a).^0.5-0.02;



xmin=18.5;
xmax=20;

[x, h] = biseccion(z, xmin, xmax, kmax, tol);
fprintf('El valor de alpha es = %.6f\n', x)

% Ahora vuelvo a definir z(t) y busco la raiz

z2= @(t) 0.04.*sqrt(19.073+t).*(1-t)-t.*sqrt(3.*19.073);

%xv=linspace(0,0.05,200);
%figure;
%hold on;
%grid on;
%plot(xv,z2(xv));
%hold off;

% La raiz esta desp de 0.02
xmin=0;
xmax=0.03;
[x_2, h_2] = secante(z2, xmin, xmax, kmax, tol);
fprintf('La raiz es = %.6f\n', x_2)

