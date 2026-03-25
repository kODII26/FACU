N = int(input("Introduce un número entero N: "))
# Inicializa un contador
contador=0
N=abs(N)
if(N==0):
    contador=1
# Usa un bucle para contar los dígitos de N
while(N>0):
    N=N//10
    contador+=1
# Imprime el número de dígitos
print(contador)
