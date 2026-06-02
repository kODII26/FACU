% x: puntos xi, i=1,2,...,n
% y: puntos yi correspondiente a f(xi), i=1,2,...,n
% df1 y dfn: valor de la derivada de f en x0 y xn
function [a,b,c,d] = cubic_spline_clamped(x,y,df)

  df1 = df(1);
  dfn = df(2);

  n = length(x);

  ai = y;

  h(1:n-1) = x(2:n) - x(1:n-1);

  % Terminos independientes
  baux(1:n) = 0;
  baux(1) = 3*((y(2)-y(1))/h(1) - df1);

  baux(2:n-1) = 3*((y(3:n)-y(2:n-1))./h(2:n-1) ...
                  - (y(2:n-1)-y(1:n-2))./h(1:n-2));

  baux(n) = 3*(dfn - (y(n)-y(n-1))/h(n-1));

  l(1) = 2*h(1);
  u(1) = 0.5;
  z(1) = baux(1)/l(1);

  for i = 2:n-1
      l(i) = 2*(x(i+1)-x(i-1)) - h(i-1)*u(i-1);
      u(i) = h(i)/l(i);
      z(i) = (baux(i)-h(i-1)*z(i-1))/l(i);
  endfor

  l(n) = h(n-1)*(2-u(n-1));
  z(n) = (baux(n)-h(n-1)*z(n-1))/l(n);

  ci(n) = z(n);

  for i = n-1:-1:1
      ci(i) = z(i) - u(i)*ci(i+1);

      bi(i) = (y(i+1)-y(i))/h(i) ...
              - h(i)*(ci(i+1)+2*ci(i))/3;

      di(i) = (ci(i+1)-ci(i))/(3*h(i));
  endfor

  a = y(1:n-1)';
  b = bi';
  c = ci(1:n-1)';
  d = di';

endfunction
