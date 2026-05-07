function [x, t] = generar_rampa(t_inicial, t_final, fm)
    t = t_inicial : (1/fm) : t_final;

    x = t .* (t >= 0);
end
