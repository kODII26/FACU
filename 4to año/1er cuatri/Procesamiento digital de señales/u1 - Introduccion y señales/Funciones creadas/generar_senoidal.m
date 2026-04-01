function [y, t] = generar_senoidal(fs, fm, phi, t_inicial, t_final)
    t = t_inicial : 1/fm : t_final; # crea vector con inicio, aumento,fin

    y = sin(2 * pi * fs * t + phi);
end
