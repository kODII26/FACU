#Matriz triangular superior
function x= sust_atras(A,b)
   n=length(b); # Si b tiene n elementos, sistema de n ecuaciones
   x=zeros(n,1); # Crea el vector columna solucion, inicialmente con ceros
   x(n)=b(n)/A(n,n);
#Al ser una matriz triangular superior, podemos despejar una ecuacion
#de la ultima fila, Ann*xn=bn -> xn=bn/Ann
#este es el unico que podemos calcular directamente
#Ahora que conozco xn, puedo subri una fila y calcular xn-1
#y asi hasta tener todo el vector xn
   for i=n-1:-1:1 # loop hacia atras
     x(i)=(b(i)-A(i,i+1:n)*x(i+1:n))/A(i,i);
#Aca hace lo mismo que arriba, despeja la ecuacion,
#pero lo hace para el i-esimo termino Xi, y va usando las X que ya obtuvo

#A(i,i+1:n) = fila i, desde la columna i+1 hasta la n
#x(i+1:n) = Vector de incognitas ya calculadas
   endfor
 endfunction

