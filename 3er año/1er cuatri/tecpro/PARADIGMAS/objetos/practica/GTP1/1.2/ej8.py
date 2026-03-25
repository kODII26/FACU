N = int(input("Introduce un número entero N para convertirlo a binario: "))
# Usa un método para convertir N a binario
binario=''
if (N==0):
    binario= '0'
else:
    while (N>0):
        binario= str(N%2)+ binario
        N= N//2

# Imprime el resultado en binario
print (binario)