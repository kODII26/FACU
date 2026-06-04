function [S] = SimpsonCompuestoDatos(x,y)
  n=length(x); #tiene que ser impar
  h= (x(n)-x(1))/(n-1);

  S0=y(1)+y(n);
  S1=0; #Suma de impares
  S2=0; #Suma de pares
  for i = 2:(n-1)
    r = mod(i,2);
    if r==0
      S1 = S1 + 4*y(i);
    else
      S2 = S2 + 2*y(i);
    endif
  endfor

  S = h*(S0 + S1 + S2) / 3;
 endfunction
