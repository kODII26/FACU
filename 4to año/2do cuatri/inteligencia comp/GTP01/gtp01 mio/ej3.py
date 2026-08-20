import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

tol = 0.0
max_epocas = 100
gamma = 0.01

def f_sign(valor):
    return 1 if valor >= 0 else -1

# OR 50% 
print("OR 50% ")
data_train = pd.read_csv("datasets/OR_50_trn.csv", header=None).to_numpy()
data_test = pd.read_csv("datasets/OR_50_tst.csv", header=None).to_numpy()

x1_train = data_train[:, 0]
x2_train = data_train[:, 1]
yd_train = data_train[:, 2]
x0_train = np.full(len(x1_train), -1)
cant_patrones_trn = len(x1_train)

x1_test = data_test[:, 0]
x2_test = data_test[:, 1]
yd_test = data_test[:, 2]
x0_test = np.full(len(x1_test), -1)
cant_patrones_tst = len(x1_test)

w0 = np.random.uniform(-0.5, 0.5)
w1 = np.random.uniform(-0.5, 0.5)
w2 = np.random.uniform(-0.5, 0.5)

miss = tol + 1
epoca = 0

while epoca < max_epocas and miss > tol:
    for i in range(cant_patrones_trn):
        y = f_sign(w0 * x0_train[i] + w1 * x1_train[i] + w2 * x2_train[i])
        error = yd_train[i] - y
        w0 = w0 + (gamma / 2) * error * x0_train[i]
        w1 = w1 + (gamma / 2) * error * x1_train[i]
        w2 = w2 + (gamma / 2) * error * x2_train[i]

    errores = 0
    for i in range(cant_patrones_trn):
        y = f_sign(w0 * x0_train[i] + w1 * x1_train[i] + w2 * x2_train[i])
        if y != yd_train[i]:
            errores += 1
    miss = errores / cant_patrones_trn
    epoca += 1

print("error entrenamiento: ", miss * 100, "%")
print("epocas: ", epoca)

errores_tst = 0
for i in range(cant_patrones_tst):
    y = f_sign(w0 * x0_test[i] + w1 * x1_test[i] + w2 * x2_test[i])
    if y != yd_test[i]:
        errores_tst += 1
miss_tst = errores_tst / cant_patrones_tst
print("error testeo: ", miss_tst * 100, "%")

# OR 90%
print("OR 90% ")
data_train = pd.read_csv("datasets/OR_90_trn.csv", header=None).to_numpy()
data_test = pd.read_csv("datasets/OR_90_tst.csv", header=None).to_numpy()

x1_train = data_train[:, 0]
x2_train = data_train[:, 1]
yd_train = data_train[:, 2]
x0_train = np.full(len(x1_train), -1)
cant_patrones_trn = len(x1_train)

x1_test = data_test[:, 0]
x2_test = data_test[:, 1]
yd_test = data_test[:, 2]
x0_test = np.full(len(x1_test), -1)
cant_patrones_tst = len(x1_test)

w0 = np.random.uniform(-0.5, 0.5)
w1 = np.random.uniform(-0.5, 0.5)
w2 = np.random.uniform(-0.5, 0.5)

miss = tol + 1
epoca = 0

while epoca < max_epocas and miss > tol:
    for i in range(cant_patrones_trn):
        y = f_sign(w0 * x0_train[i] + w1 * x1_train[i] + w2 * x2_train[i])
        error = yd_train[i] - y
        w0 = w0 + (gamma / 2) * error * x0_train[i]
        w1 = w1 + (gamma / 2) * error * x1_train[i]
        w2 = w2 + (gamma / 2) * error * x2_train[i]

    errores = 0
    for i in range(cant_patrones_trn):
        y = f_sign(w0 * x0_train[i] + w1 * x1_train[i] + w2 * x2_train[i])
        if y != yd_train[i]:
            errores += 1
    miss = errores / cant_patrones_trn
    epoca += 1

print("error entrenamiento: ", miss * 100, "%")
print("epocas: ", epoca)

errores_tst = 0
for i in range(cant_patrones_tst):
    y = f_sign(w0 * x0_test[i] + w1 * x1_test[i] + w2 * x2_test[i])
    if y != yd_test[i]:
        errores_tst += 1
miss_tst = errores_tst / cant_patrones_tst
print("error testeo: ", miss_tst * 100, "%")

#conclusiones
print("\nAnalisis:")
print("Con 50% de desviacion los datos se superponen mas, pero el perceptron aun puede encontrar una frontera razonable")
print("Con 90% de desviacion los datos se mezclan mucho, el perceptron no logra separar las clases con 0% de error")
print("y llega al maximo de epocas sin converger, necesitaria un modelo mas complejo o aceptar un error mayor")

#grafico OR 50%
plt.figure()
plt.title("OR 50% - Entrenamiento")
plt.scatter(x1_train[yd_train == 1], x2_train[yd_train == 1], color='blue', marker='o', label='Clase 1')
plt.scatter(x1_train[yd_train == -1], x2_train[yd_train == -1], color='red', marker='x', label='Clase -1')
x_linea = np.linspace(-2, 2, 100)
y_linea = w0 / w2 - (w1 / w2) * x_linea
plt.plot(x_linea, y_linea, color='green', label='Frontera')
plt.xlim(-2, 2)
plt.ylim(-2, 2)
plt.xlabel("x1")
plt.ylabel("x2")
plt.legend()
plt.grid(True)
plt.show()

#grafico OR 90%
plt.figure()
plt.title("OR 90% - Entrenamiento")
plt.scatter(x1_train[yd_train == 1], x2_train[yd_train == 1], color='blue', marker='o', label='Clase 1')
plt.scatter(x1_train[yd_train == -1], x2_train[yd_train == -1], color='red', marker='x', label='Clase -1')
x_linea = np.linspace(-2, 2, 100)
y_linea = w0 / w2 - (w1 / w2) * x_linea
plt.plot(x_linea, y_linea, color='green', label='Frontera')
plt.xlim(-2, 2)
plt.ylim(-2, 2)
plt.xlabel("x1")
plt.ylabel("x2")
plt.legend()
plt.grid(True)
plt.show()

