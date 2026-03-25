N = int(input("¿Cuántos números vas a introducir? "))
# Inicializa una variable para guardar el máximo valor
max=0
# Usa un bucle para solicitar N números y encontrar el máximo
for x in range(0,N,1):
    num=float(input("Introduce numero "))
    if(num>max):
        max=num


# Imprime el número máximo
print(max)
