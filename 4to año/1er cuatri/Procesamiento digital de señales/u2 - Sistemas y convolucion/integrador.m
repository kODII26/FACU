#parte 2
N=20;
x=zeros(1,N);
x(1)=1; #seria el delta[0]
h=zeros(1,N);
for n=1:N
    if n==1
        h(1)=x(1); % h[0]
    else
        h(n)=x(n)+0.2*x(n-1)+0.6*h(n-1);
    end
end

figure;
subplot(2,1,1);
stem(h, 'filled', 'MarkerFaceColor', 'r');
title('Respuestas a los impulsos h[n]');
subplot(2,1,2);
stem(x, 'filled', 'MarkerFaceColor', 'g');
title('Entrada x[n]');

%parte 3
L=10;
x= ones(1,L);

%obtener salida mediante 3 metodos:

%1ero: sumatoria convolucion lineal
y1=conv_lineal(x,h); %long=29

%2do: utilizando representacion matricial de la convolucion
%las columnas de H son la señal h(n) desplazada
%las filas de H representan como se calcula una muestra concreta de la salida
%la fila 1 sirve para calcular y[0], la 2 para y[1], ...
long_salida = length(x) + length(h) - 1;   % 29
H = zeros(long_salida, length(x));

for col = 1:length(x)
    H(col:col+length(h)-1, col) = h'; %traspone para que sea un vector columna y insertarlo en la matriz
endfor

%x viene como fila, 1x10, no puedo multiplicarlo con una matriz 29x10
%lo paso a columna 10x1
%numero de columnas de la matriz debe ser igual a numero de filas del vector

y2 = H * x';   % queda vector columna
%cada fila de esta mult hace la suma de la conv lineal
y2 = y2';      % lo paso a fila para compararlo con y1 e y3

%3ro: convolucion circular con modificaciones para que coincida con la lineal
x_ext= [ x zeros(1,length(h)-1)];
h_ext=[ h zeros(1,length(x)-1)];

y3=conv_circular(x_ext, h_ext);

% comparar visualmente las 3 salidas
n_y = 0:length(y1)-1;

figure;

subplot(3,1,1);
stem(n_y, y1, 'filled', 'MarkerFaceColor', 'r');
title('Salida por sumatoria de convolucion');
grid on;

subplot(3,1,2);
stem(n_y, y2, 'filled', 'MarkerFaceColor', 'g');
title('Salida por representacion matricial');
grid on;

subplot(3,1,3);
stem(n_y, y3, 'filled', 'MarkerFaceColor', 'b');
title('Salida por convolucion circular con modficacion');
grid on;





