[x, fs] = audioread('escala.wav');
t_segmento = 0.5;
L = round(t_segmento * fs); %cantidad de muestras por nota

% referencia para LA (440 Hz)
n = 0:L-1;
referencia_LA = sin(2 * pi * 440 * n / fs);
%en señales discretas t=n/fs


for i = 1:8
  % marco inicio y fin de cada nota
    inicio = (i-1)*L + 1;
    fin = i*L;
    segmento = x(inicio:fin);

    % prod interno
    parecido(i) = abs(dot(segmento, referencia_LA));
end

% busco el maximo
[valor, posicion] = max(parecido);
fprintf('La nota LA se encuentra en el segmento: %d\n', posicion);
fprintf('Tiempo de inicio: %.2f segundos\n', (posicion-1)*t_segmento);
