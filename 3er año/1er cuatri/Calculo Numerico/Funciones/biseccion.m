function [x, h] = biseccion(f, xmin, xmax, kmax, tol)
  %if f(xmin) * f(xmax) > 0
  %  error('Error: La función no cambia de signo en los extremos del intervalo.');
  %endif
  a = xmin;
  b = xmax;
  h = [];
  x_prev = a;

  for k = 1:kmax
    x = (a + b)/2;
    h(end+1) = x;

    % ---------------------------------------------------------
    % CRITERIO 1: Corte por valor de la función (Residuo)
    % Se detiene cuando la imagen f(x) es lo suficientemente cercana a cero.
    % ---------------------------------------------------------
    #if abs(f(x)) < tol
    #  return;
    #endif

    % ---------------------------------------------------------
    % CRITERIO 2: Corte por Error Absoluto
    % Se detiene cuando la cota del error garantizado es menor a la tolerancia.
    % (También se podría usar abs(x - x_prev) < tol)
    % ---------------------------------------------------------
    if abs(b - a)/2 < tol
      return;
    endif

    % ---------------------------------------------------------
    % CRITERIO 3: Corte por Error Relativo
    % Se detiene cuando la diferencia relativa entre iteraciones es pequeña.
    % Se exige k > 1 para que haya una iteración anterior con cual comparar,
    % y x ~= 0 para evitar una división por cero.
    % ---------------------------------------------------------
    #if k > 1 && x ~= 0 && (abs(x - x_prev) / abs(x)) < tol
    #  return;
    #endif


    if f(a)*f(x) < 0
      b = x;
    else
      a = x;
    endif
  endfor
endfunction
