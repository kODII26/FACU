function [y_inv,t] = inversion(y,t)
    %inversion: y_inv = y(-t)
    %Esto funciona si el vector de tiempos esta centrado en t=0
    y_inv = y(end:-1:1);

    %[valor,indice] = min(abs(t));
    %y_inv = y(indice:end);
    %y_inv = [y_inv y(1:indice-1)];
endfunction

#Hay DOS tipos de inversión posibles:

# 1. Inversión de amplitud: xinv​[n]=−x[n] -> y_inv = -y;
# 2. Inversión temporal: x[n]→x[−n] -> y_inv = y(end:-1:1);

