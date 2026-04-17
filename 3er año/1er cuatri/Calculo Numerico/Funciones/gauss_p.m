function [x,r] = gauss_p(A,b)
  n=length(b);
  A=[A b];
  r=1:n; % [1 2 3 ... n]
  epsilon=1e-9; % Tolerancia para detectar pivotes casi nulosz
  for k=1:n-1
    % la funcion max devuelve
    % pmax: el pivote de mayor valor absoluto
    % p: posicion donde se encuentra pmax (local)
    [pmax,p] = max(abs(A(r(k:n),k))); % Mira la coluumna k de la matriz A pero solo desde las filas k hasta n respetando el orden de r
    if pmax<epsilon
      disp(’Los posibles pivots son CERO’)
      break
    endif
    p = p+k-1; %actualizamos pos. a numeracion global
    if p~=k % Si p distinto de k hay que actualizar pivote
      r([p k])= r([k p]); %actualiza el pivote
    endif
    A(r(k+1:n),k) = A(r(k+1:n),k)/A(r(k),k);
    A(r(k+1:n),k+1:n+1) = A(r(k+1:n),k+1:n+1) - A(r(k+1:n),k)*A(r(k),k+1:n+1);
    endfor
  x=sust_atras(A(r,:));

