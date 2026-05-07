#Generación del Ruido: La función randn de Octave genera ruido aleatorio con distribución normal de varianza 1 y media 0
#.Para que tenga una varianza de 0.5, debemos multiplicarlo por su desviación estándar (la raíz cuadrada de la varianza:  0.5).
fm = 1000;
N = 500;
t = (0:N-1) / fm;

f_seno = 100;        # Frecuencia de la senoidal
senoidal = sin(2 * pi * f_seno * t); # Señal senoidal sin ruido

#Ruido aleatorio con distribución normal (media 0, varianza 0.5)
varianza = 0.5;
desviacion_std = sqrt(varianza);
ruido = desviacion_std * randn(1, N);

#entonces la senal queda definida como:
x = senoidal + ruido;

#graficamos la senal
%figure;
%plot(t, x, 'b', 'LineWidth', 1.2);
%title('Señal compuesta x[n] (Senoidal 100Hz + Ruido Gaussiano)');
%xlabel('Tiempo (s)');
%ylabel('Amplitud');
%grid on;
%pause(10);

#Energía: Como establece la teoría geométrica de señales, la energía es exactamente igual al cuadrado de la norma-2 (E(x)=∣∣x∣∣^2.)
norma_2 = norm(x, 2);
#Energía (Cuadrado de la norma-2)
energia = norma_2^2;
#Valor RMS (Raíz cuadrada de la Energía dividida por N)
valor_rms = sqrt(energia / N);
# Acción (Equivalente a la Norma-1)
accion = norm(x, 1);
#Amplitud (Equivalente a la Norma-infinito)
amplitud = norm(x, inf);
#resultados:
printf('\n--- RESULTADOS PARTE I ---\n');
printf('Norma-2:   %8.4f\n', norma_2);
printf('Energía:   %8.4f\n', energia);
printf('Valor RMS: %8.4f\n', valor_rms);
printf('Acción:    %8.4f\n', accion);
printf('Amplitud:  %8.4f\n', amplitud);


######################################################################
#parte 2
#El Producto Interno: En el espacio de señales, el producto interno ⟨x,y⟩ se calcula sumando el producto muestra a muestra de ambos vectores
#.Conceptualmente, nos proporciona una medida directa del grado de parecido o la proyección de una señal sobre la otra.
#El Ángulo: La teoŕıa geométrica establece que el producto interno se relaciona con el ángulo φ que
#forman los dos vectores mediante la ecuación ⟨x,y⟩=∥x∥2 ∥y∥2 cos(φ).
#Si despejamos φ aplicando la función arco coseno (acos), podemos obtener el ángulo exacto.

y = sin(2 * pi * 100 * t);
#ahora hacemos prod interno
prod_interno = sum(x .* y);

#para calcular el angulo entre dos senales despejamos de la formula: ⟨x,y⟩=∥x∥2 ∥y∥2 cos(φ).
#donde nos queda: cos(φ) = <x,y> / (||x|| * ||y||)
norma_y = norm(y, 2);
coseno_angulo = prod_interno / (norma_2 * norma_y);
#como ya tenemos el coseno del angulo si aplicamos el arco coseno obtenemos el angulo:
angulo_rad = acos(coseno_angulo);
#y en grados:
angulo_grados = angulo_rad * (180 / pi);

#el producto interno normalizado (que equivale al cos(φ)) es una medida directa de la similitud o el "aporte de una señal en otra".
    #Si el ángulo fuera de 0° (cos(0)=1), significaría que las señales son iguales o idénticas en forma.
    #Si el ángulo fuera de 90° (cos(90)=0), las señales serían completamente ortogonales, es decir, no se parecen en nada y no comparten información.

printf('\n--- RESULTADOS PARTE II ---\n');
printf('Producto Interno <x, y>: %8.4f\n', prod_interno);
printf('Coseno del ángulo:       %8.4f\n', coseno_angulo);
printf('Ángulo entre señales:    %8.4f rad (%8.2f grados)\n', angulo_rad, angulo_grados);

#Conclusión : Al calcular el coseno de 44.89°, el resultado ronda el 0.708. Esto demuestra que existe una similitud fuerte y positiva (aprox. 71%) entre ambas señales.
#¿Por qué no dio 0° si ambas tienen 100 Hz? Porque el ruido aleatorio gaussiano que le sumaste a x[n] aporta energía en otras direcciones
#no correlacionadas, lo que "desvía" o inclina el vector alejándolo del 0° perfecto.
#Sin embargo, como el producto interno actúa como un "detector", logró encontrar la senoidal pura escondida debajo del ruido,
#evitando que el ángulo se acerque a los 90° (ortogonalidad).




####################################################################################################################
#parte 3:
#si un conjunto es ortonormal, el producto interno de la señal consigo misma da 1 (∣∣x∣∣=1) y el producto cruzado da 0.
#Una onda senoidal pura "cruda" es ortogonal a otra de distinta frecuencia, pero su norma no es 1.
#Para hacerlas verdaderamente ortonormales, debemos dividirlas por su propia norma-2.

#Coeficientes de Proyección (α):si la base es ortonormal, el coeficiente óptimo α i
#que minimiza el error se calcula simplemente como el producto interno directo entre tu señal y el vector de la base:
#α i=⟨x,ϕi⟩

#Error Cuadrático Total (ECT):el cuadrado de la norma-2 del vector de error (la diferencia entre la señal original x y tu aproximación
#x~).Es decir, ECT=∣∣x−x~∣∣2^2.Norma dos al cuadrado.

#hacemos las bases ortogonales
phi1_cruda = sin(2 * pi * 100 * t);
phi2_cruda = sin(2 * pi * 200 * t);

#Para que la base sea verdaderamente ortonormal, su norma-2 debe ser 1.
phi1 = phi1_cruda / norm(phi1_cruda, 2);
phi2 = phi2_cruda / norm(phi2_cruda, 2);

#procedemos a hallar los alfas usando la fórmula: alfa = <x, phi>
alfa1 = sum(x .* phi1);
alfa2 = sum(x .* phi2);

# construimos la señal aproximada (~x)
x_aprox = alfa1 * phi1 + alfa2 * phi2;

#calculamos el ect con la formula: ECT = ||x - x_aprox||^2, usando la norma-2.
error_senial = x - x_aprox;
ECT = norm(error_senial, 2)^2;

#% resultados
printf('\n--- RESULTADOS PARTE III ---\n');
printf('Coeficiente Alfa 1 (proyección en 100 Hz): %8.4f\n', alfa1);
printf('Coeficiente Alfa 2 (proyección en 200 Hz): %8.4f\n', alfa2);
printf('Error Cuadrático Total (ECT):              %8.4f\n', ECT);

# graficamos para ver la limpieza de la senal.
figure;
plot(t, x, 'c', 'DisplayName', 'Señal Original Ruidosa (x)');
hold on;
plot(t, x_aprox, 'k', 'LineWidth', 1.5, 'DisplayName', 'Aproximación (\sim x)');
title('Aproximación de x[n] sobre base \phi_1 y \phi_2');
xlabel('Tiempo (s)');
ylabel('Amplitud');
legend;
xlim([0 0.1]); % Hacemos zoom en las primeras 0.1s para ver los ciclos claramente
grid on;
pause(10);


#######################################################################################
#parte 4:
#nueva senal desfasada pi/2
frecuencia_ref = 100;
fase_desfase = pi / 2;
y_desfasada = sin(2 * pi * frecuencia_ref * t + fase_desfase);

#volvemos a calcular el prod interno
prod_interno_desfasado = sum(x .* y_desfasada);

#calculamos el angulo para verificar si es ortogonal o no
norma_y_desfasada = norm(y_desfasada, 2);
coseno_angulo_desfasado = prod_interno_desfasado / (norma_2 * norma_y_desfasada);

angulo_rad_desfasado = acos(coseno_angulo_desfasado);
angulo_grados_desfasado = angulo_rad_desfasado * (180 / pi);

printf('\n--- RESULTADOS PARTE IV ---\n');
printf('Producto Interno (sin desfase):     %8.4f\n', prod_interno); % Valor de la Parte II
printf('Producto Interno (con desfase 90°): %8.4f\n', prod_interno_desfasado);
printf('Nuevo ángulo entre señales:         %8.2f grados\n', angulo_grados_desfasado);
