function x = sust_adelante_vec(A)

    n = size(A,1);

    x = zeros(n,1);

    x(1) = A(1,end) / A(1,1);

    for i = 2:n

        x(i) = (A(i,end) - A(i,1:i-1)*x(1:i-1)) / A(i,i);

    endfor

endfunction
