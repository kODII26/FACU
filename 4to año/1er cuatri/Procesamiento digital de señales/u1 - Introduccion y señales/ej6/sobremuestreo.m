#T: periodo de muestreo original -> 1/fm
#Ti: nuevo periodo de muestreo
#n: indice de muestra de la señal original
#m: indice de muestra de la señal sobremuestreeada

#COmo hay que muestrear a 4 veces la f original:
# fi=4*fm

#La nueva señal tendra muestras cada 0,025s no 0,1s.
#Esa es la idea de interpolar, meter muestras nuevas
#entre las viejas

#x(n): valores originales
#xi(m): valores que quiero construir

function [yi, ti] = sobremuestreo_sinc(y, t, fm, factor)

    # Periodos
    T = 1/fm;
    Ti = 1/(factor * fm);

    # Nuevo eje temporal
    ti = t(1):Ti:t(end);

    # Inicialización (sin esto anda igual)
    # yi = zeros(size(ti));

    # Interpolación sinc
    for m = 1:length(ti)
        suma = 0;
        for n = 1:length(t)
            u = (ti(m) - t(n)) / T;

            if u == 0
                I = 1;
            else
                I = sin(pi*u)/(pi*u);
            endif

            suma = suma + y(n) * I;  % x(nT) * I(...)
        endfor
        yi(m) = suma; % resultado final xi(mTi)
    endfor

endfunction

#El valor de u representa la distancia normalizada entre una muestra
#original y una muestra interpolada, y se utiliza como argumento
#de la función interpolante para determinar el peso de cada
#muestra en la reconstrucción.











