function [x,it,r_h]=gauss_seidel(A,b,x0,maxit,tol)

  n=length(b);
  it=0;
  r_h=[];
  x=x0;

  tic;

  while (it<maxit)

    it+=1;

    for i=1:n

      x(i) = ( b(i) ...
             - A(i,1:i-1)*x(1:i-1) ...
             - A(i,i+1:n)*x0(i+1:n) ) / A(i,i);

    endfor

    % =========================
    % CRITERIOS DE CORTE
    % =========================

    % 1) Error relativo entre iteraciones
    %err = norm(x-x0,inf)/norm(x,inf);

    % 2) Norma infinita del residuo
    %err = norm(b-A*x, inf);

    % 3) Norma infinita del residuo relativo
    %err = norm(b-A*x, inf)/norm(b,inf);

    % 4) Error absoluto
    err = norm(x-x0,inf);

    r_h=[r_h;err];

    if(err<tol)
      break;
    endif

    x0=x;

  endwhile

  t=toc

  if it==maxit
    disp('Se ha llegado al Nro maximo de iteraciones')
  endif

end
