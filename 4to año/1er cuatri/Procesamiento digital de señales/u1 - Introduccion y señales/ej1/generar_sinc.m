function [y,t] = generar_sinc(fs, fm, t_inicial, t_final)
  t = t_inicial : 1/fm : t_final;

  x = 2 * pi * fs * t;

  y = ones(size(x));

  # Indices donde x NO es 0
  indices = find(x!=0); #find genera un vector donde se cumpla la condicion

  y(indices) = sin(x(indices)) ./ x(indices);
  # x(indices) para modificar solo donde x!= 0
  # tambien para garantizar que no divida por cero (grave error)
  # luego modifica solo donde no es cero el vector y
endfunction
