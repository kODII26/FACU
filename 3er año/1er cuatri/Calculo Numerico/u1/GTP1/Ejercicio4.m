

valores_n = [10, 100, 1000, 2000]
for n = valores_n
  printf('n es: ', n)

  a=randi([1,10],1,n) # Vector de 1 fila, n columnas, con valores entre 1 y 10
  b=randi([1,10],1,n)


  # Forma original
  tic
  suma=0
  for i=1:n
    for j=1:i
      suma += a(i)*b(j)
    endfor
  endfor
  tiempo1= toc
  endfor
  # Forma optimizada


