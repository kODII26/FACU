function [x, rh, t] = puntofijo(g, x0, kmax, tol)
  %g(x) es la funcion con x despejada por ej: f(x)=x^2+x+2
  %x=-x^2-2  --> g(x)=-x^2-2
  tic();
  it = 0;
  while it < kmax
    x = g(x0);
    rh(it+1) = abs(x - x0);
    %rh(it) = max(abs([fp,p-a]));
    if rh(it+1) < tol
      break;
    endif
    x0 = x;
    it++;
  endwhile
  t = toc();
endfunction
