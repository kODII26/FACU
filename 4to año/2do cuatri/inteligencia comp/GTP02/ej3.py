import matplotlib.pyplot as plt
import numpy as np
import pandas as pd


tasas = [0.01, 0.1, 0.5] # distintas tasas de aprendizaje a probar
capas = [4, 8, 3] 
max_epocas = 1000
tol = 0.001


data_train = pd.read_csv("iris81_trn.csv", header=None).to_numpy()
data_test = pd.read_csv("iris81_tst.csv", header=None).to_numpy()


# 4 entradas (columnas 0 a 3) y 3 salidas (columnas 4 a 6)
X_train = data_train[:, :4]
Yd_train = data_train[:, 4:]  # matriz de 3 columnas 

X_test = data_test[:, :4]
Yd_test = data_test[:, 4:]

cant_patrones_trn = len(X_train)
cant_patrones_tst = len(X_test)

#funcion de activacion sigmoide (-1, 1)
def sigmoide(x):
    return (2 / (1 + np.exp(-x))) - 1

def sigmoide_derivada(x):
    s = sigmoide(x)
    return (1 + s) * (1 - s) / 2

#clases posibles (codigo binario)
clases = {
    "setosa":     np.array([-1, -1, 1]),
    "versicolor": np.array([-1, 1, -1]),
    "virginica":  np.array([1, -1, -1])
}

#funcion para clasificar: comparo la salida con cada clase y elijo la mas cercana
def clasificar(y):
    menor_dist = float('inf')
    clase = None
    for nombre, codigo in clases.items():
        dist = np.sum((y - codigo) ** 2)
        if dist < menor_dist:
            menor_dist = dist
            clase = codigo
    return clase #retorna el codigo de la clase mas parecida 

#funcion para propagar un patron por la red (forward)
def forward(pesos, cant_capas, x):
    entrada = x
    for c in range(cant_capas - 1):
        entrada_con_bias = np.concatenate(([-1], entrada))
        lin = np.dot(pesos[c], entrada_con_bias)
        entrada = sigmoide(lin) #la salida obtenida se convierte en la entrada de la siguiente capa
    return entrada #al terminar de propagar, devuelve la salida de la ultima capa 

#pruebo con distintas tasas de aprendizaje
cant_capas = len(capas)

for gamma in tasas:
    print("=" * 50)
    print("Tasa de aprendizaje: ", gamma)
    print("=" * 50)

    # inicializo pesos aleatoriamente
    pesos = []
    np.random.seed(42)

    #creo los pesos de cada capa
    for c in range(1, cant_capas):
        w = np.random.uniform(-0.5, 0.5, (capas[c], capas[c-1] + 1))
        pesos.append(w)

    # entrenamiento con backpropagation
    print("Entrenamiento")

    epoca = 0
    ecm = tol + 1
    ecm_por_epoca = [] # para graficar curva de error cuadratico
    miss_por_epoca = []# para graficar curva de error de clasificacion

    while epoca < max_epocas and ecm > tol:
        suma_error2 = 0

        for p in range(cant_patrones_trn):
            #forward (propagacion hacia adelante)
            lineales = []
            salidas = []

            entrada = X_train[p]

            for c in range(cant_capas - 1):
                entrada_con_bias = np.concatenate(([-1], entrada))
                lin = np.dot(pesos[c], entrada_con_bias)
                sal = sigmoide(lin)
                lineales.append(lin)
                salidas.append(sal)
                entrada = sal

            # la salida de la ultima capa es la salida de la red
            y = salidas[-1]

            yd = Yd_train[p]

            # error del patron
            error = yd - y
            suma_error2 += np.sum(error ** 2)

            #backward (retropropagacion del error)
            deltas = [None] * (cant_capas - 1)

            # delta de la capa de salida
            deltas[-1] = error * sigmoide_derivada(lineales[-1])

            # deltas de las capas ocultas
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

                entrada_con_bias = np.concatenate(([-1], entrada_capa))
                pesos[c] += gamma * np.outer(deltas[c], entrada_con_bias)

        # error cuadratico medio de la epoca
        ecm = suma_error2 / cant_patrones_trn
        ecm_por_epoca.append(ecm)

        # calculo error de clasificacion de la epoca
        errores = 0
        for p in range(cant_patrones_trn):
            y = forward(pesos, cant_capas, X_train[p])
            y_clase = clasificar(y)
            if not np.array_equal(y_clase, Yd_train[p]):
                errores += 1
        miss_por_epoca.append(errores / cant_patrones_trn * 100)

        epoca += 1

    print("Epocas utilizadas:", epoca)
    print("ECM final:", round(ecm, 6))

    # evaluacion en entrenamiento
    print("\nResultados entrenamiento:")
    errores_trn = 0
    for p in range(cant_patrones_trn):
        y = forward(pesos, cant_capas, X_train[p])
        y_clase = clasificar(y)
        if not np.array_equal(y_clase, Yd_train[p]):
            errores_trn += 1

    miss_trn = errores_trn / cant_patrones_trn
    print("Error de clasificacion:", miss_trn * 100, "%")

    # evaluacion en testeo
    print("\nResultados testeo:")
    errores_tst = 0
    for p in range(cant_patrones_tst):
        y = forward(pesos, cant_capas, X_test[p])
        y_clase = clasificar(y)
        if not np.array_equal(y_clase, Yd_test[p]):
            errores_tst += 1

    miss_tst = errores_tst / cant_patrones_tst
    print("Error de clasificacion:", miss_tst * 100, "%")

    # grafico curva de ECM por epoca
    plt.figure()
    plt.title("ECM por epoca - Iris (gamma=" + str(gamma) + ")")
    plt.plot(range(1, len(ecm_por_epoca) + 1), ecm_por_epoca, color='blue')
    plt.xlabel("Epoca")
    plt.ylabel("Error cuadratico medio")
    plt.grid(True)
    plt.show()

    # grafico curva de error de clasificacion por epoca
    plt.figure()
    plt.title("Error de clasificacion por epoca - Iris (gamma=" + str(gamma) + ")")
    plt.plot(range(1, len(miss_por_epoca) + 1), miss_por_epoca, color='red')
    plt.xlabel("Epoca")
    plt.ylabel("Error de clasificacion (%)")
    plt.grid(True)
    plt.show()
