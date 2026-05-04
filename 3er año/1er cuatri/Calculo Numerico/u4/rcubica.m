function [x]=rcubica(a)
  f= @(x) x.^3-a;

  % 2. Definimos el intervalo inicial dinámico según el valor de 'a'
  if a > 0
    xmin = 0;
    xmax = max(1, a);
    %Si a > 0, sabemos que la raíz estará entre 0 y a
  else
    xmin = min(-1, a);
    xmax = 0;
    %Si a < 0, por simetría, un intervalo seguro es [min(-1, a), 0].
  endif

  % 3. Límite de iteraciones (100 es más que suficiente para bisección en double)
  kmax = 100;

  % 4. Adaptación de la tolerancia
  % Como biseccion.m usa error absoluto, calculamos la tolerancia absoluta
  % necesaria para garantizar un error RELATIVO menor a 1e-12.
  tol_abs = (abs(a)^(1/3)) * 1e-12;

  % 5. Llamada a la función del inciso (b)
  [x, h] = biseccion(f, xmin, xmax, kmax, tol_abs);

endfunction

