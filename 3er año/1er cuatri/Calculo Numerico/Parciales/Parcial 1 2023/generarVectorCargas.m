function b = generarVectorCargas(n)
  x = linspace(0,1,41)';
  h = x(2)-x(1); 
  b = zeros(n,1);
  
  for i = 1:n
    b(i) = (h^2)*20.*exp(-10.*(x(i+1)-0.7).^2);
  endfor


b(1) = b(1)+5;
b(n) = b(n)+6;

endfunction  