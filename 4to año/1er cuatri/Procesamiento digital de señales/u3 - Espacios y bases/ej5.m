x = load('te.txt');
fm = 11025;


% Ventanas (definidas a mano)

ventanas = [17100 21400;
            29900 34200;
            39600 43200;
            48500 52800;
            59000 63200;
            70000 73900;
            81000 85100];

figure;
plot(x);
hold on;
for k = 1:size(ventanas,1)
    xline(ventanas(k,1), 'g', 'LineWidth', 1.5); % Inicio en verde
    xline(ventanas(k,2), 'r', 'LineWidth', 1.5); % Fin en rojo
end
title('Señal de audio con las ventanas fijas');
xlabel('Número de muestra');
ylabel('Amplitud');


% Frecuencias DTMF

f_filas = [697, 770, 852, 941];
f_cols  = [1209, 1336, 1477];

% Teclado
teclado = ['1','2','3';
           '4','5','6';
           '7','8','9';
           '*','0','#'];


% Loop por cada número
for k = 1:size(ventanas,1)

    % extraer segmento
    ini = ventanas(k,1);
    fin = ventanas(k,2);
    segmento = x(ini:fin);

    % tiempo local
    N = length(segmento);
    t = (0:N-1)'/fm; %en señales discretas t=n/fm
    % traspongo porque segmento tambien es columna y luego multiplico ambas

    % DETECCIÓN FILA
    magnitud_filas = zeros(1,length(f_filas));

    for i = 1:length(f_filas)
        f = f_filas(i);
        %la señal puede venir desfasada por eso se hace seno y coseno
        seno = sin(2*pi*f*t);
        coseno = cos(2*pi*f*t);

        % productos internos
        pi_seno = sum(segmento .* seno);
        pi_cos  = sum(segmento .* coseno);

        %magnitud total (elimina el efecto de la fase)
        %hay que eliminar la fase porque puede generar un falso negativo
        magnitud_filas(i) = sqrt(pi_seno^2 + pi_cos^2);
    end


    % DETECCIÓN COLUMNA
    magnitud_col = zeros(1,length(f_cols));

    for i = 1:length(f_cols)
        f = f_cols(i);

        seno = sin(2*pi*f*t);
        coseno = cos(2*pi*f*t);

        pi_seno = sum(segmento .* seno);
        pi_cos  = sum(segmento .* coseno);

        magnitud_col(i) = sqrt(pi_seno^2 + pi_cos^2);
    end


    % Obtener índice máximo

    [~, idx_fila] = max(magnitud_filas);
    [~, idx_col]  = max(magnitud_col);

    numero = teclado(idx_fila, idx_col);

    fprintf('Número %d detectado: %c\n', k, numero);
end
