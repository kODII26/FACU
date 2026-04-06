#A Triangular inferior

function x= sust_adelante(A,b)
  n=length(b);
  x=zeros(n,1);
  x(1)=b(1)/A(1,1);
  for i=2:1:n #Empieza en 2 ya que la 1 ya la calculamos arriba
    x(i)=(b(i)-A(i,1:i-1)*x(1:i-1))/A(i,i);
  endfor

  endfunction
