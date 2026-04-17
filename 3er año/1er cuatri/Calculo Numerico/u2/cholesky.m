function L = cholesky1(A)
  n = length(A);
  L = zeros(n,n);

  L(1,1) = sqrt(A(1,1));

  for i = 2:n
    L(i,1) = A(i,1)/L(1,1);
  endfor

  for i = 2:n-1
    L(i,i) = sqrt(A(i,i) - L(i,1:i-1)*L(i,1:i-1)');

    for j = i+1:n
      L(j,i) = (A(j,i) - L(j,1:i-1)*L(i,1:i-1)') / L(i,i);
    endfor
  endfor

  L(n,n) = sqrt(A(n,n) - L(n,1:n-1)*L(n,1:n-1)');
endfunction

%El teorema dice que una matriz simétrica A es definida positiva si y solo si puede hacerse
%eliminación gaussiana sin intercambio de filas, con pivotes positivos; además en ese caso los
%cálculos son estables
%El corolario dice que una matriz simétrica A es definida positiva si y solo si puede factorizarse
%como LL

