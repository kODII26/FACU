function [x, t] = generar_aleatoria(t_inicial, t_final, fm)
   t = t_inicial : (1/fm) : t_final;
   x = randn(1, length(t));
end
