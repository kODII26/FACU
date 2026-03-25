N = int(input("¿Cuántos números deseas promediar? "))
suma = 0
# Usa un bucle para solicitar N números, sumarlos y luego calcular la media
for x in range(0,N,1):
    num=float(input("Introduce numero a sumar "))
    suma+=num

# Imprime la media
print(suma/N)
