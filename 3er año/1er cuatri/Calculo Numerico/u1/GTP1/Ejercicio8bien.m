valores_n = [10, 100, 1000, 2000];
for n = valores_n
  a = randi([1,10], 1, n);       % vector de 1 fila, n columnas y valores entre 1 y 10
  b = randi([1,10], 1, n);       % <-- ;
  printf("=== n = %d ===\n", n);
  tic;
  suma1 = 0;                     % <-- ;
  for i = 1:n
    for j = 1:i
      suma1 += a(i) * b(j);      % <-- ;
    endfor
  endfor
  tiempo1 = toc;                 % <-- ;
  tic;
  suma2 = 0;                     % <-- ;
  acumulado_a = zeros(1, n);     % <-- ;
  acumulado_a(n) = a(n);         % <-- ;
  for j = n-1:-1:1
    acumulado_a(j) = acumulado_a(j+1) + a(j);  % <-- ;
  end
  for j = 1:n
    suma2 += b(j) * acumulado_a(j);  % <-- ;
  end
  tiempo2 = toc;                 % <-- ;
  printf("Forma original:   suma = %d, tiempo = %.6f s\n", suma1, tiempo1);
  printf("Forma optimizada: suma = %d, tiempo = %.6f s\n", suma2, tiempo2);
end
