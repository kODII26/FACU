A=[1 2 3; 4 5 6;  7 8 9]

mat=A'

C= [-3.2 , 5 , 7.4 , 6 ; 4 , 17 , -1.3 , 2.1 , ; 5.9 , -6 , 0 , 4.5 ]

C(1:2.2:4)

C(:,3) # MUESTRA todos los elementos de la oclumna 3

C(2,:) # muestra todos los elemntos de la fila 2

zeros(5,2) # da una matriz 5*2 de ceros

ones(2,3) # matriz 2*3 de unos

v= diag(A) # devuelve la diagonal principal de a

D= diag(v,1) # te corre la diagonal 1 columna


