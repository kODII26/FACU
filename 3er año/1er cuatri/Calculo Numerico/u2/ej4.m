A= [1 -1 2 -1 ; 0 2 -1 1 ; 0 0 -1 -1 ; 0 0 0 2];
b= [-8 6 -4 4]';

x= sust_atras(A,b)


At= A';
x=sust_adelante(At,b)

