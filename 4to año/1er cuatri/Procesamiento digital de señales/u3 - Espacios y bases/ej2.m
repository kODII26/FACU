addpath('../Funciones creadas');

fm = 1000;
t = 0:(1/fm):1-(1/fm);
f_ref = 5;

% senal de referencia
x_ref = sin(2 * pi * f_ref * t);

%Evalue el efecto que producen los distintos parametros
%(A, f, φ) sobre el calculo del producto interno.

% vario la amplitud
fprintf('\n--- Variando AMPLITUD (f=5Hz, fase=0) ---\n');
amplitudes = [0.5, 1, 2];
for A = amplitudes
    x_test = A * sin(2 * pi * f_ref * t);
    % calculo de producto interno
    %prod_int = (x_ref*x_test')/(norm(x_ref)*norm(x_test));
    prod_int = sum(x_ref .* x_test);
    fprintf('Amplitud %.1f -> Producto Interno: %.2f\n', A, prod_int);
end

% vario la frecuencia
fprintf('\n--- Variando FRECUENCIA (A=1, fase=0) ---\n');
frecuencias = [5, 5.5, 6, 10];
for f = frecuencias
    x_test = 1 * sin(2 * pi * f * t);
    prod_int = sum(x_ref .* x_test);
    fprintf('Frecuencia %.1f Hz -> Producto Interno: %.2f\n', f, prod_int);
end

% vario la fase
fprintf('\n--- Variando FASE (A=1, f=5Hz) ---\n');
fases = [0, pi/2, pi]; % 0 grados, 90 grados, 180 grados
nombres_fases = {'0', 'pi/2 (90 grados)', 'pi (180 grados)'};
for i = 1:length(fases)
    x_test = 1 * sin(2 * pi * f_ref * t + fases(i));
    prod_int = sum(x_ref .* x_test);
    fprintf('Fase %s -> Producto Interno: %.2f\n', nombres_fases{i}, prod_int);
end

% conclusiones
% amplitud: vemos que el prod interno es directamente proporcional a la amplitud
% al aumentar la amplitud, el vector señal aumenta su norma y por lo tanto tambien
% su proyeccion sobre la señal de referencia

% frecuencia: al cambiar las frecuencias las oscilaciones dejan de coincidir
% y el producto interno tiende a cero

% fase: vemos que en el caso de 90 grados las señales quedan ortogonales por lo tanto
% se vuelven cero, y en el caso de 180 se invierte el producto interno
