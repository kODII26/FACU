function [y, t] = generar_cuadrada(fs, fm, phi, t_inicial, t_final)
    t = t_inicial : 1/fm : t_final;

    argumento_mod = mod(2 * pi * fs * t + phi, 2 * pi);

    y = ones(size(t));

    y(argumento_mod >= pi) = -1;
endfunction
