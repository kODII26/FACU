function U = generarMatrizU_ciclos(n)

  %Armado de la matriz U
  for i = 1:n
    for j = 1:n
      if i == j
        U(i,j) = 2; %Diagonal principal
      elseif abs(i-j) == 1
        U(i,j) = -1; %Diagonal superior e inferior
      endif
    endfor
  endfor
  
endfunction