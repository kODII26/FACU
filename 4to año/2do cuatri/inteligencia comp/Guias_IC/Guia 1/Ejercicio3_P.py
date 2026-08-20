import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

def funcActivacion(result):
    return 1 if result >= 1 else -1

# Leer CSV sin encabezado
data_train = pd.read_csv("OR_90_trn.csv", header=None)
data_test = pd.read_csv("OR_90_tst.csv", header=None)

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
epocas=2
# Entrenamiento
for epocas in range(epocas):
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



# Comparar entrenamiento
correct_train = ypredictrain == ytrain
print("Cantidad de aciertos en entrenamiento:", np.sum(correct_train), "de", len(ytrain))

# Comparar test
correct_test = ypredictest == ytest
print("Cantidad de aciertos en test:", np.sum(correct_test), "de", len(ytest))


# --- Puntos de entrenamiento ---
plt.figure(figsize=(6,6))
for i in range(len(x1train)):
    if ytrain[i] == 0:
        plt.scatter(x1train[i], x2train[i], color='red', marker='o', label='Clase 0' if i==0 else "")
    else:
        plt.scatter(x1train[i], x2train[i], color='blue', marker='s', label='Clase 1' if i==0 else "")

plt.xlabel("x1")
plt.ylabel("x2")
plt.title("Puntos de entrenamiento")
plt.legend()
plt.grid(True)
plt.show()

# --- Puntos de test ---
plt.figure(figsize=(6,6))
for i in range(len(x1test)):
    if ytest[i] == 0:
        plt.scatter(x1test[i], x2test[i], color='red', marker='o', label='Clase 0' if i==0 else "")
    else:
        plt.scatter(x1test[i], x2test[i], color='blue', marker='s', label='Clase 1' if i==0 else "")

plt.xlabel("x1")
plt.ylabel("x2")
plt.title("Puntos de test")
plt.legend()
plt.grid(True)
plt.show()
