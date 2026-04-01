addpath('../Funciones creadas');

#Parte 1
A=5;
fs=10;
phi=pi/4;
fm=400;
t_inicial=0;
t_final=1;
[y,t]= generar_senoidal(fs,fm,phi,t_inicial,t_final);
y=A*y;

figure(1); plot(t,y); title('Señal original')

#Clasificacion morfologica: Es una señal muestreada
#TIEMPO DISCRETO: Ya que nuestra var ind, es t la cual esta definida de la forma
# t_inicial : 1/fm : t_final . O sea va dando saltos, no contiene TODOS los posibles valores
#AMPLITUD CONTINUA: La amplitud es continua ya que la señal puede tomar cualquier valor
#cuando cuantizamos deja de ser continua ya que se escalona, pero la señal original es continua.

#Clasificacion fenomenologica: Es una señal deterministica periódica y sinusoidal
#Es deterministica ya que la creamos nosotros con parametros que elegimos por lo tanto
#podemos calcular su valor en cualquier instante
#Ademas al ser sinusoidal y periodica podemos garantizar que será deterministica ya
#que se repite en el tiempo

[y_rec,t] = rectificacion(y,t);
figure(2); plot(t,y_rec); title('Señal rectificada');

[y_cuantizada,t] = cuantizacion(y_rec,t,16);
figure(3); plot(t,y_cuantizada); title('Señal cuantizada 16');

#Parte 2

varianza= 2;
ruido1 = randn(size(y_cuantizada));
ruido1 = varianza .* ruido1;

varianza= 5;
ruido2 = randn(size(y_cuantizada));
ruido2 = varianza .* ruido2;

sen1= y_cuantizada+ruido1;
figure(4); plot(t,sen1); title('Ruido 1');

sen2= y_cuantizada+ruido2;
figure(5);plot(t,sen2); title('Ruido 2');

#Calculo potencia de la señal cuantizada del inciso 1 y de los ruidos del inciso 2
potSen= potencia(y_cuantizada);
potRui1= potencia(ruido1);
potRui2= potencia(ruido2);

#Necesito hallar un k para que la SNR sea de 6db, voy a usar el ruido1
k= sqrt(potSen/(10^0.6*potRui1));
ruido1= k .* ruido1;
potRui1= potencia(ruido1);

#Calculo SNR para verificar que sea 6db
snr= 10*log10(potSen/potRui1)

#Parte 3
%   item1
%Si se reduce el numero de bits en la cuantizacion entonces los valores de amplitud presentarian
%saltos mas grandes, lo que impide representar correctamente la forma de la funcion

%   item2
%Si la frecuencia de muestreo se redujera a 15hz, nuestra señal muestreada no podria representar correctamente la
%señal original, ya que es necesario que fm>=2*fs, comenzaria a ocurrir el fenomeno de aliasing, en el cual observamos
%una señal de menor frecuencia debido a una mala eleccion para la frecuencia de muestreo.
%Ademas si la frecuencia de muestreo se redujera a 15hz, entonces en un periodo habria niveles de la cuantizacion
%que no serian utilizados

%   item3
%Multiplicaria el ruido por una constante k que respete la siguiente restriccion k = sqrt(Ps/Pr)
%donde Ps es la potencia de la señal sin ruido y Pr es la potencia del ruido original, sin escalar



