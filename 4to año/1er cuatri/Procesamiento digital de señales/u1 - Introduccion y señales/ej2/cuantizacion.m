function [y_cuantizada,t] = cuantizacion(y,t,N)

    minimo = min(y);
    y_pos = y - minimo;

    H = max(y_pos)/(N-1);

    y_cuantizada = H * floor(y_pos / H);

    % Saturación superior
    y_cuantizada(y_pos >= (N-1)*H) = (N-1)*H;

    % Volver al rango original
    y_cuantizada = y_cuantizada + minimo;

endfunction
