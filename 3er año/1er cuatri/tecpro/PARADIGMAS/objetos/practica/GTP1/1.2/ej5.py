N = int(input("Introduce un número para generar su tabla de multiplicar: "))
mult=0
for x in range(0,11,1):

    result=N*mult
    print (N,'por ',mult,'=',result)
    mult+=1
# Usa un bucle para generar y mostrar la tabla de multiplicar de N
