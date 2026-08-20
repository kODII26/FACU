import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

tol = 0.0            # tolerancia de error (0 = quiero 0% de error)
max_epocas = 100     # maximo de epocas de entrenamiento
gamma = 0.01         # tasa de aprendizaje

#lectura
data_train = pd.read_csv("datasets/OR_trn.csv", header=None).to_numpy()
data_test = pd.read_csv("datasets/OR_tst.csv", header=None).to_numpy()

cant_patrones_trn = len(data_train)
cant_patrones_tst = len(data_test)

#separo entradas y salidas deseadas
x1_train = data_train[:, 0]# columna 1 x1
x2_train = data_train[:, 1]# columna 2 x2
yd_train = data_train[:, 2]# columna 3 yd

x1_test = data_test[:, 0]
x2_test = data_test[:, 1]
yd_test = data_test[:, 2]

#funcion d activacion
def f_sign(valor):
    return 1 if valor >= 0 else -1

#columna del bias , siempre -1
x0_train = np.full(cant_patrones_trn, -1)
x0_test = np.full(cant_patrones_tst, -1)

#inicializo los pesos aleatoriamente
w0 = np.random.uniform(-0.5, 0.5)
w1 = np.random.uniform(-0.5, 0.5)
w2 = np.random.uniform(-0.5, 0.5)

print("entrenamiento")

miss = tol + 1   # arranco con un error mayor a la tolerancia para entrar al while
epoca = 0

while epoca < max_epocas and miss > tol:
    for i in range(cant_patrones_trn):
        y = f_sign(w0 * x0_train[i] + w1 * x1_train[i] + w2 * x2_train[i])
        error = yd_train[i] - y
        w0 = w0 + (gamma / 2) * error * x0_train[i]
        w1 = w1 + (gamma / 2) * error * x1_train[i]
        w2 = w2 + (gamma / 2) * error * x2_train[i]

    #calculo el error total de la epoca
    errores = 0
    for i in range(cant_patrones_trn):
        y = f_sign(w0 * x0_train[i] + w1 * x1_train[i] + w2 * x2_train[i])
        if y != yd_train[i]:
            errores += 1

    miss = errores / cant_patrones_trn
    epoca += 1

print("pesos finales: ", w0, w1, w2)
print("error de entrenamiento: ",miss * 100,"%")
print("epocas utilizadas: ",epoca)

#testing
print("testeo")

errores_tst = 0
for i in range(cant_patrones_tst):
    y = f_sign(w0 * x0_test[i] + w1 * x1_test[i] + w2 * x2_test[i])
    if y != yd_test[i]:
        errores_tst += 1

miss_tst = errores_tst / cant_patrones_tst
print("error de testeo: ",miss_tst * 100,"%")

#grafico de entrenamiento
plt.figure()
plt.title("Entrenamiento - OR")
plt.scatter(x1_train[yd_train == 1], x2_train[yd_train == 1],
            color='blue', marker='o', label='Clase 1')
plt.scatter(x1_train[yd_train == -1], x2_train[yd_train == -1],
            color='red', marker='x', label='Clase -1')


x_linea = np.linspace(-1.5, 1.5, 100)
y_linea = w0 / w2 - (w1 / w2) * x_linea
plt.plot(x_linea, y_linea, color='green', linestyle='-', label='Frontera de decision')
plt.xlim(-1.5, 1.5)
plt.ylim(-1.5, 1.5)
plt.xlabel("x1")
plt.ylabel("x2")
plt.legend()
plt.grid(True)
plt.show()

#grafico de testeo
plt.figure()
plt.title("Testeo - OR")
plt.scatter(x1_test[yd_test == 1], x2_test[yd_test == 1],
            color='blue', marker='o', label='Clase 1')
plt.scatter(x1_test[yd_test == -1], x2_test[yd_test == -1],
            color='red', marker='x', label='Clase -1')

plt.plot(x_linea, y_linea, color='green', linestyle='-', label='Frontera de decision')
plt.xlim(-1.5, 1.5)
plt.ylim(-1.5, 1.5)
plt.xlabel("x1")
plt.ylabel("x2")
plt.legend()
plt.grid(True)
plt.show()
