m=5
n=4*m+1
x=linspace(0,1,n) # vector de 0 a n, y que el valor final tiene que ser 1 (octave divide cuanto tiene q valer cada cosa)
y=zeros(1,n)

a=x(1:m+1) # guarda en a, los elementos de x desde 1 hasta m+1

y(1:m+1)= sin(2*pi*a) #reemplaza desde 1 hasta m+1 por el valor del sen

plot(x,y)

