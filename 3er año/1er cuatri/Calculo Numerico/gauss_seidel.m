function [x,it,r_h]=gauss_seidel(A,b,x0,maxit,tol)
  n=length(b);it=0;r_h=[];x=x0;
  tic;
  while (it<maxit)
    it+=1;
      for i=1:n
        x(i) = (b(i)-A(i,1:i-1)*x(1:i-1)-A(i,i+1:n)*x0(i+1:n))/A(i,i);
      endfor
    err=norm(x-x0,inf)/norm(x,inf);
    % Calcula la norma de cuanto cambio la solucion entre la ultima iteracion y la actual
    % Luego la normaliza (no es lo mismo cambiar 0,02 de 5000 que de 1)
    % Si err es muy grande, todavia estamos lejos de estabilizarnos
    r_h=[r_h;err];
    if(err<tol)
      break;
    endif
    x0=x;
  endwhile
  t=toc;
  if it==maxit
  disp('Se ha llegado al Nro maximo de iteraciones')
endif
