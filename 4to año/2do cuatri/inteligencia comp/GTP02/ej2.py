import matplotlib.pyplot as plt
import numpy as np
import pandas as pd


capas = [2, 6,4, 1]    
gamma = 0.1 # tasa de aprendizaje
max_epocas = 1000  # maximo de epocas
tol = 0.05 # tolerancia del error cuadratico medio


data_train = pd.read_csv("concent_trn.csv", header=None).to_numpy()
data_test = pd.read_csv("concent_tst.csv", header=None).to_numpy()

# separo entradas y salidas deseadas
X_train = data_train[:, :-1] # todas las columnas menos la ultima
Yd_train = data_train[:, -1] # ultima columna = salida deseada

X_test = data_test[:, :-1]
Yd_test = data_test[:, -1]

cant_patrones_trn = len(X_train)
cant_patrones_tst = len(X_test)

# funcion de activacion sigmoide (-1, 1)
def sigmoide(x):
    return (2 / (1 + np.exp(-x))) - 1

def sigmoide_derivada(x):
    s = sigmoide(x)
    return (1 + s) * (1 - s) / 2

# inicializo pesos aleatoriamente
# pesos[c] = matriz de pesos de la capa c
# la primera columna de cada matriz es el peso del bias (entrada -1)
cant_capas = len(capas)
pesos = []

np.random.seed(42)  

#creo los pesos de cada capa
for c in range(1, cant_capas):
    w = np.random.uniform(-0.5, 0.5, (capas[c], capas[c-1] + 1)) #filas: cuantas neuronas hay en esta capa
                                                                #columnas:  cuantas entradas tiene cada neurona
    # +1 por el bias
    pesos.append(w) # pesos0 contiene matriz de pesos de la capa oculta
                    # pesos1 contiene matriz de pesos de la capa de salida

# entrenamiento con backpropagation
print("Entrenamiento")

epoca = 0
ecm = tol + 1 #arranco con un error mayor a la tolerancia

while epoca < max_epocas and ecm > tol:
    suma_error2 = 0

    for p in range(cant_patrones_trn):
        #forward (propagacion hacia adelante)
        lineales = []
        salidas = []

        entrada = X_train[p] # entrada del patron actual

        for c in range(cant_capas - 1):
            # agrego el -1 del bias al inicio de la entrada
            entrada_con_bias = np.concatenate(([-1], entrada))
            lin = np.dot(pesos[c], entrada_con_bias)
            sal = sigmoide(lin)
            lineales.append(lin)
            salidas.append(sal)
            entrada = sal  #la salida de esta capa es la entrada de la siguiente

        # la salida de la ultima capa es la salida de la red
        y = salidas[-1]

        # salida deseada 
        yd = Yd_train[p]

        # error del patron
        error = yd - y
        suma_error2 += np.sum(error ** 2)

        #backward (retropropagacion del error)
        # calculo los deltas de cada capa (de atras para adelante)

        deltas = [None] * (cant_capas - 1) #creo lista vacia para reservarlugares

        # delta de la capa de salida
        deltas[-1] = error * sigmoide_derivada(lineales[-1])

        # deltas de las capas ocultas (solo se usan los pesos sin el bias para propagar)
        for c in range(cant_capas - 3, -1, -1):
            # pesos[c+1][:, 1:] = pesos sin la columna del bias
            #.T traspone, la matriz tiene q estar trasp. para que coincidan las dimensiones
            #con el vector de deltas
            deltas[c] = sigmoide_derivada(lineales[c]) * np.dot(pesos[c+1][:, 1:].T, deltas[c+1])

        # actualizo pesos
        for c in range(cant_capas - 1):
            if c == 0:
                entrada_capa = X_train[p]
            else:
                entrada_capa = salidas[c-1]

            # agrego el -1 del bias a la entrada
            entrada_con_bias = np.concatenate(([-1], entrada_capa))
            pesos[c] += gamma * np.outer(deltas[c], entrada_con_bias)

    # error cuadratico medio de la epoca
    ecm = suma_error2 / cant_patrones_trn
    epoca += 1

print("Epocas utilizadas:", epoca)
print("ECM final:", round(ecm, 6))

# funcion para propagar un patron por la red (forward)
def forward(x):
    entrada = x
    for c in range(cant_capas - 1):
        entrada_con_bias = np.concatenate(([-1], entrada))
        lin = np.dot(pesos[c], entrada_con_bias)
        entrada = sigmoide(lin)
    return entrada

# evaluacion en entrenamiento
print("\nResultados entrenamiento:")
errores_trn = 0
for p in range(cant_patrones_trn):
    y = forward(X_train[p])
    y_clase = 1 if y[0] >= 0 else -1
    if y_clase != Yd_train[p]:
        errores_trn += 1

miss_trn = errores_trn / cant_patrones_trn
print("Error de clasificacion:", miss_trn * 100, "%")

# evaluacion en testeo
print("\nResultados testeo:")
errores_tst = 0
for p in range(cant_patrones_tst):
    y = forward(X_test[p])
    y_clase = 1 if y[0] >= 0 else -1
    if y_clase != Yd_test[p]:
        errores_tst += 1

miss_tst = errores_tst / cant_patrones_tst
print("Error de clasificacion:", miss_tst * 100, "%")

# grafico de clasificacion entrenamiento
plt.figure()
plt.title("Clasificacion - Concentrico Entrenamiento")
plt.scatter(X_train[Yd_train == 1, 0], X_train[Yd_train == 1, 1],
            color='blue', marker='o', label='Clase 1')
plt.scatter(X_train[Yd_train == -1, 0], X_train[Yd_train == -1, 1],
            color='red', marker='x', label='Clase -1')

# dibujo la region de decision
x_min, x_max = X_train[:, 0].min() - 0.5, X_train[:, 0].max() + 0.5
y_min, y_max = X_train[:, 1].min() - 0.5, X_train[:, 1].max() + 0.5
xx, yy = np.meshgrid(np.linspace(x_min, x_max, 200),
                      np.linspace(y_min, y_max, 200))

Z = np.zeros(xx.shape)
for i in range(xx.shape[0]):
    for j in range(xx.shape[1]):
        sal = forward(np.array([xx[i, j], yy[i, j]]))
        Z[i, j] = sal[0]

plt.contourf(xx, yy, Z, levels=[-1, 0, 1], colors=['#ffcccc', '#ccccff'], alpha=0.5)
plt.contour(xx, yy, Z, levels=[0], colors='green', linewidths=2)
plt.xlabel("x1")
plt.ylabel("x2")
plt.legend()
plt.grid(True)
plt.show()

# grafico de clasificacion testeo
plt.figure()
plt.title("Clasificacion - Concentrico Testeo")
plt.scatter(X_test[Yd_test == 1, 0], X_test[Yd_test == 1, 1],
            color='blue', marker='o', label='Clase 1')
plt.scatter(X_test[Yd_test == -1, 0], X_test[Yd_test == -1, 1],
            color='red', marker='x', label='Clase -1')

plt.contourf(xx, yy, Z, levels=[-1, 0, 1], colors=['#ffcccc', '#ccccff'], alpha=0.5)
plt.contour(xx, yy, Z, levels=[0], colors='green', linewidths=2)
plt.xlabel("x1")
plt.ylabel("x2")
plt.legend()
plt.grid(True)
plt.show()