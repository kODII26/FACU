import numpy as np
import pandas as pd

def funcActivacion(result):
    return 1 if result >= 1 else -1

# Leer CSV sin encabezado
data_train = pd.read_csv("OR_trn.csv", header=None)
data_test = pd.read_csv("OR_tst.csv", header=None)

# Columnas de entrenamiento
x1train = data_train.iloc[:, 0].to_numpy()
x2train = data_train.iloc[:, 1].to_numpy()
ytrain = data_train.iloc[:, 2].to_numpy()
colx0_train = np.full(len(x1train), -1)

# Columnas de test
x1test = data_test.iloc[:, 0].to_numpy()
x2test = data_test.iloc[:, 1].to_numpy()
ytest = data_test.iloc[:, 2].to_numpy()
colx0_test = np.full(len(x1test), -1)

# Pesos iniciales
w0 = 0.35  
w1 = 0.35
w2 = 0.35
gamma=0.01
epocas = 4

# Entrenamiento
for epoca in range(epocas):
    for i in range(len(x1train)):
        y_lin = w0 * colx0_train[i] + w1 * x1train[i] + w2 * x2train[i]
        y_lin = 1 if y_lin >= 0 else -1
        # error
        error = ytrain[i] - y_lin
        # actualizar pesos
        w0 += gamma * error * colx0_train[i]
        w1 += gamma * error * x1train[i]
        w2 += gamma * error * x2train[i]

    ypredictrain = np.zeros(len(x1train))
    for i in range(len(x1train)):
        y_lin = w0 * colx0_train[i] + w1 * x1train[i] + w2 * x2train[i]
        y_lin = 1 if y_lin >= 0 else -1
        ypredictrain[i] = y_lin

    ypredictest = np.zeros(len(x1test))
    for i in range(len(x1test)):
        y_lin = w0 * colx0_test[i] + w1 * x1test[i] + w2 * x2test[i]
        y_lin = 1 if y_lin >= 0 else -1
        ypredictest[i] = y_lin


print("Predicciones de entrenamiento:", ypredictrain)
print("Salida original:", ytrain)
print("Predicciones de test:", ypredictest)
print("Salida test:", ytest)
import numpy as np

# Comparar entrenamiento
correct_train = ypredictrain == ytrain
print("Coincidencias en entrenamiento:", correct_train)
print("Cantidad de aciertos en entrenamiento:", np.sum(correct_train), "de", len(ytrain))

# Comparar test
correct_test = ypredictest == ytest
print("Coincidencias en test:", correct_test)
print("Cantidad de aciertos en test:", np.sum(correct_test), "de", len(ytest))
print(w0)
print(w1)
print(w2)
