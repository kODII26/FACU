% PARTE 1: CÁLCULO DE COEFICIENTES Y RECONSTRUCCIÓN (BASE ORTONORMAL)
% las funciones de Legendre son orto normales entre -1 y 1

% tomo muestras para discretizar la señal
dt = 0.001;
t = -1:dt:1;

% funcion escalon
f = -1.*(t<0) + 1.*(t>=0);

% calculo bases de Legendre ORTONORMALIZADAS
phi0 = (1/sqrt(2)) * ones(size(t));
phi1 = sqrt(3/2) * t;
phi2 = sqrt(5/2) * (1.5*t.^2 - 0.5);
phi3 = sqrt(7/2) * (2.5*t.^3 - 1.5*t);

% calculo de coeficientes por proyeccion ortonormal
a0 = sum(f .* phi0) * dt;
a1 = sum(f .* phi1) * dt;
a2 = sum(f .* phi2) * dt;
a3 = sum(f .* phi3) * dt;
% estos coeficientes son los que daran un menor error

% ecuacion de aproximacion
f_aprox = a0*phi0 + a1*phi1 + a2*phi2 + a3*phi3;
% si agregamos terminos el error se tendria que ir reduciendo

% error cuadratico total
ECT = sum((f - f_aprox).^2) * dt;


fprintf('Coeficientes Calculados (Discretos):\n');
fprintf('alpha_0 = %8.4f  |  Teorico: 0\n', a0);
fprintf('alpha_1 = %8.4f  |  Teorico: %.4f (sqrt(3/2))\n', a1, sqrt(3/2));
fprintf('alpha_2 = %8.4f  |  Teorico: 0\n', a2);
fprintf('alpha_3 = %8.4f  |  Teorico: %.4f (-sqrt(7/32))\n', a3, -sqrt(7/32));
fprintf('Error (ECT) = %.4f\n\n', ECT);

figure(1);
plot(t, f, 'r--', 'LineWidth', 2); hold on;
plot(t, f_aprox, 'b-', 'LineWidth', 2);
grid on;
xlabel('t');
ylabel('Amplitud');
legend('y(t) = Escalón', 'Aproximacion (4 términos)', 'Location', 'northwest');
title('Aproximacion de función escalón con Legendre Ortonormal');

% PARTE 2: SUPERFICIE DE ERROR 3D (VARIANDO COEFICIENTES)

% Como a0 y a2 son cero, variamos a1 y a3 para ver cómo cambia el error
a1_opt = a1;
a3_opt = a3;
variacion = 0.5;

% Creamos los vectores de variación
a1_vec = linspace(a1_opt - variacion, a1_opt + variacion, 40);
a3_vec = linspace(a3_opt - variacion, a3_opt + variacion, 40);

% Creamos la malla
[A1, A3] = meshgrid(a1_vec, a3_vec);

% Inicializamos matriz de superficie de error
ECT_surf = zeros(size(A1));

% Calculamos el error para CADA combinación posible en la malla
for i = 1:size(A1, 1)
    for j = 1:size(A1, 2)
        % Mantenemos a0 y a2 fijos (en su valor óptimo), y variamos a1 y a3
        aprox_var = a0*phi0 + A1(i,j)*phi1 + a2*phi2 + A3(i,j)*phi3;
        ECT_surf(i,j) = sum((f - aprox_var).^2)*dt;
    end
end

% Generamos la figura 3D
figure(2);
surf(A1, A3, ECT_surf, 'EdgeColor', 'none'); % Superficie
hold on;

% Marcamos el punto óptimo calculado en el inciso 1
plot3(a1_opt, a3_opt, ECT, 'r*', 'MarkerSize', 15, 'LineWidth', 3);
hold off;

xlabel('\alpha_1 (Variaciones)');
ylabel('\alpha_3 (Variaciones)');
zlabel('Error Cuadrático Total (ECT)');
title('Superficie del Error - Paraboloide 3D');
colormap jet; colorbar;

% PARTE 3: EVOLUCIÓN DEL ERROR AL AGREGAR TÉRMINOS
phi4 = sqrt(9/2) * (1/8) * (35 * t.^4 - 30 * t.^2 + 3);
phi5 = sqrt(11/2) * (1/8) * (63 * t.^5 - 70 * t.^3 + 15 * t);

a4 = sum(f .* phi4) * dt;
a5 = sum(f .* phi5) * dt;

% Aproximaciones sucesivas agregando términos (usando phi en vez de P)
aprox_1 = a0*phi0;
aprox_2 = aprox_1 + a1*phi1;
aprox_3 = aprox_2 + a2*phi2;
aprox_4 = aprox_3 + a3*phi3;
aprox_5 = aprox_4 + a4*phi4;
aprox_6 = aprox_5 + a5*phi5;


% ECT para cada caso
ect_1 = sum((f - aprox_1).^2)*dt;
ect_2 = sum((f - aprox_2).^2)*dt;
ect_3 = sum((f - aprox_3).^2)*dt;
ect_4 = sum((f - aprox_4).^2)*dt;
ect_5 = sum((f - aprox_5).^2)*dt;
ect_6 = sum((f - aprox_6).^2)*dt;

fprintf('\n--- Evolución del Error Cuadrático Total (ECT) ---\n');
fprintf('ECT con 1 término  (phi0):             %.6f\n', ect_1);
fprintf('ECT con 2 términos (phi0, phi1):       %.6f\n', ect_2);
fprintf('ECT con 3 términos (phi0..phi2):       %.6f\n', ect_3);
fprintf('ECT con 4 términos (phi0..phi3):       %.6f\n\n', ect_4);
fprintf('ECT con 5 términos (phi0..phi4):       %.6f\n\n', ect_5);
fprintf('ECT con 6 términos (phi0..phi5):       %.6f\n\n', ect_6);


% Graficamos para ver cómo la curva se va pegando a la original
figure(3);
plot(t, f, 'k', 'LineWidth', 2); hold on;
plot(t, aprox_1, 'r--');
plot(t, aprox_2, 'g--');
plot(t, aprox_3, 'm--');
plot(t, aprox_4, 'r--');
plot(t, aprox_5, 'g--');
plot(t, aprox_6, 'b-', 'LineWidth', 1.5);

grid on;
title('Aproximaciones sucesivas agregando términos');
legend('Escalón Original', ...
       '1 Término (\phi_0)', ...
       '2 Términos (\phi_0 a \phi_1)', ...
       '3 Términos (\phi_0 a \phi_2)', ...
       '4 Términos (\phi_0 a \phi_3)', ...
       '5 Términos (\phi_0 a \phi_4)', ...
       '6 Términos (\phi_0 a \phi_5)', ...
       'Location', 'northwest');
