function [S]= SimpsonCompuesto(f,a,b,L)
  #L : numero de subintervalos
  #f : funcion a integrar
  #a y b extremos del intervalo
  #I valor de la integral
  h = (b-a)/(2*L);
  x0i = f(a) + f(b);
  x1i = 0; #Suma de f(x2i-1)
  x2i = 0; #Suma de f(x2i)
  for i=1:(L)
    x = a + (2*i-1)*h;
    x1i = x1i + f(x);
  endfor

   for i=1:(L-1)
    x = a + (2*i)*h;
    x2i = x2i + f(x);
  endfor

  S = h*(x0i + 2*x2i + 4*x1i) / 3;


