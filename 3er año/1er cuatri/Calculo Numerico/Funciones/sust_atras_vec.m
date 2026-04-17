function x = sust_atras_vec(A,b)
  n = length(b);
  x = zeros(n,1);
  x(n) = b(n)/A(n,n);
  for i = n-1:-1:1
    suma = A(i,i+1:n)*x(i+1:n);
    x(i) = (b(i)-suma)/A(i,i);
  endfor

#A(i,i+1:n) → la parte de la fila 𝑖 a la derecha de la diagonal
#x(i+1:n) → las incógnitas ya conocidas
#y hacés directamente el producto matricial


#como vectorizar: vectorizar sirve para reducir el costo computacional
# amplias la matriz: A= [A b] te queda de n+1 * n
# hallas longitud
# inicializas el vector x en cero
# hallas xn desp haces el for para los otros x
# y sigue todo igual a la funcion sin vectorizar
# hay que vectorizar el ultimo lazo(el de for j)
