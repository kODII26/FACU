import csv
import numpy as np
import matplotlib.pyplot as plt

# Guia 1 - Ejercicio 2

# Datos de Entrenamiento
entradas = []
salidas = []

<<<<<<< Updated upstream
# Abrimos y leemos el archivo, guardamos los valores en los vectores entradas y salidas.
with open('OR_trn.csv', mode='r', encoding='utf-8') as archivo:
=======
with open('XOR_trn.csv', mode='r', encoding='utf-8') as archivo:
>>>>>>> Stashed changes
    lector = csv.reader(archivo)
    for fila in lector:
        x1, x2, yd = map(float, fila)
        entradas.append([-1, x1, x2])  # Agregar x0 = -1
        salidas.append(yd) # Y_deseada

# Entrenamiento del Perceptrón
np.random.seed(0)
pesos = np.random.uniform(-0.5, 0.5, 3)  # Vector de 3 valores entre -0.5 y 0.5

<<<<<<< Updated upstream
def funcActivacion(result): # Funcion Signo
    return 1 if result >= 0 else -1
=======
np.random.seed(0)  # para reproducibilidad
pesos = np.random.uniform(-0.5, 0.5, 3) # Pesos random entre -0.5 y 0.5
gamma = 0.01
epocas = 1  # cantidad de epocas
>>>>>>> Stashed changes

gamma = 0.01 # Tasa de aprendizaje 
max_epocas = 10  # Numero maximo de epocas

# Graficamos las entradas
plt.figure(figsize=(8, 6))
for i in range(len(entradas)):
    if salidas[i] == 1:
        plt.scatter(entradas[i][1], entradas[i][2], color="blue", marker="o", label="Clase 1" if i == 0 else "")
    else:
        plt.scatter(entradas[i][1], entradas[i][2], color="red", marker="x", label="Clase -1" if i == 0 else "")

total_iters = max_epocas * len(entradas)
iter_count = 0

# Entrena y grafica
for epoca in range(max_epocas):
    y = []  # reinicio lista por epoca, salida y
    errores_epoca = 0   
    for i in range(len(entradas)): # Itera sobre cada patron (fila) de entrenamiento
        potencial = np.dot(entradas[i], pesos)
        y.append(funcActivacion(potencial))

        error = salidas[i] - y[i] # y_deseada - y
        # Actualizamos los pesos
        for j in range(len(pesos)):
            pesos[j] += gamma * error * entradas[i][j] # Si el error = 0 -> no se modifica. 

        if error != 0:
            errores_epoca += 1

        #  Dibuja frontera en cada iteracion (cada patron)
        x_vals = np.linspace(-2, 2, 100)
        if pesos[2] != 0: # Evita division por 0
            y_vals = (pesos[0] - pesos[1]*x_vals) / pesos[2] # Recta 
            alpha = (iter_count + 1) / total_iters
            plt.plot(x_vals, y_vals, color="black", alpha=alpha)

        iter_count += 1

    print(f"Época {epoca+1}: errores = {errores_epoca}")

# Resultados entrenamiento
print("Pesos modificados:", pesos)

# Salidas con pesos entrenados
y_e = [] # y_entrenados
for i in range(len(entradas)):
    potencial = np.dot(entradas[i], pesos)
    y_e.append(funcActivacion(potencial))

aciertos = 0
for i in range(len(y_e)):
    if y_e[i] == salidas[i]:
        aciertos += 1

print("\nResultados Entrenamiento:")
print("Cantidad de casos entrenamiento:", len(salidas))
print("Casos exitosos entrenamiento:", aciertos)
print("Pesos finales:", pesos)

# Mostrar evolucion de la frontera
plt.xlabel("x1")
plt.ylabel("x2")
plt.title("Evolucion de la frontera de decision")
plt.legend()
plt.grid(True)
plt.show()

# Datos de Test
entradastest = []
salidastest = []

with open('OR_tst.csv', mode='r', encoding='utf-8') as archivo:
    lector = csv.reader(archivo)
    for fila in lector:
        x1, x2, yd = map(float, fila)
        entradastest.append([-1, x1, x2])  # Agregar x0 = -1
        salidastest.append(yd)

# Evaluación con Test
ytest = []
for i in range(len(entradastest)):
    potencial = np.dot(entradastest[i], pesos)
    ytest.append(funcActivacion(potencial))

aciertostest = 0
for i in range(len(ytest)):
    if ytest[i] == salidastest[i]:
        aciertostest += 1

print("\nResultados Test:")
print("Cantidad de casos test:", len(salidastest))
print("Casos exitosos test:", aciertostest)
