function [x, rh, it, t] = secante(f, x0, x1, kmax, tol)

%f: la función de la cual se desea encontrar la raíz.
%x0 y x1 valores entre la funcion

  tic();
  it = 0;
  fx0 = f(x0);
  fx1 = f(x1);

  if sign(fx0)*sign(fx1) > 0
    error(' Los limites del intervalo medidos en f son del mismo signo');
  endif

  while it < kmax
    x = x1 - fx1*(x1 - x0)/(fx1 - fx0);
    fx = f(x);
    rh(it+1) = abs(fx);
    if rh(it+1) < tol && abs(x - x1) < tol
      break;
    endif
    fx0 = fx1;
    fx1 = fx;
    x0 = x1;
    x1 = x;
    it++;
  endwhile
  t = toc();
endfunction
