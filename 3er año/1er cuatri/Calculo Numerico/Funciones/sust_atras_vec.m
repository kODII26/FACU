function x = sust_atras_vec(A)
    n = size(A, 1);
    x = zeros(n, 1);
    x(n) = A(n, end) / A(n, n);
    for i = n-1:-1:1
        x(i) = (A(i, end) - A(i, i+1:n) * x(i+1:n)) / A(i, i);
    end
end
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
