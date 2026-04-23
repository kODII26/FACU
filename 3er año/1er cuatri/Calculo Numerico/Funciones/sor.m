% Para que SOR converja, es necesario que 0 < w < 2

% Si A es simetrica definida positiva, entonces SOR converje para todo w en (0,2)

function [x,it,r_h,t] = sor(A,b,x0,maxit,tol,w)
  n = length(b);
  it = 0;
  r_h = [];
  x = x0;
  tic;
  while (it < maxit)
    it += 1;

    for i = 1:n
      S = A(i,1:i-1)*x(1:i-1) + A(i,i+1:n)*x0(i+1:n);
      x(i) = (1-w)*x0(i) + w*(b(i)-S)/A(i,i);
    endfor

    err = norm(x-x0,inf)/norm(x,inf);
    r_h = [r_h; err];

    if (err < tol)
      break;
    endif

    x0 = x;
  endwhile

  t=toc;
  if it == maxit
    disp('Se ha llegado al Nro maximo de iteraciones')
  endif
endfunction


