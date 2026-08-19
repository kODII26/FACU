from learn_perceptron import learn_perceptron
from test_perceptron import test_perceptron
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
tol=0.00
max_epocas=100
tasa=0.001
training = "datasets/OR_trn.csv"
print("APRENDIZAJE --------------------")
[w, miss, epocas] = learn_perceptron(training, tol, max_epocas, tasa)
print("El error del aprendizaje fue de: ",miss*100,"%")
print("La cantidad de epocas para el aprendizaje fue de: ",epocas)

M = pd.read_csv(training,header=None).to_numpy()
x1 = M[:,0]
x2 = M[:,1]
clases = M[:,2]

#Graficamos los puntos reales separando por clase (1 y -1)
plt.scatter(x1[clases == 1], x2[clases == 1], color='blue', marker='o', label='Clase 1')
plt.scatter(x1[clases == -1], x2[clases == -1], color='red', marker='x', label='Clase -1')
#Generamos dos puntos x para trazar la línea
y_linea = w[0]/w[2] - w[1]/w[2]*x1
plt.plot(x1, y_linea, color='green', linestyle='-', label='Frontera')
plt.legend()
plt.show()



print("TESTEO --------------------")
testing = "datasets/OR_tst.csv"
miss = test_perceptron(w,testing)
print("El error en el testeo fue de: ",miss*100,"%")

M = pd.read_csv(testing,header=None).to_numpy()
x1 = M[:,0]
x2 = M[:,1]
clases = M[:,2]

#Graficamos los puntos reales separando por clase (1 y -1)
plt.scatter(x1[clases == 1], x2[clases == 1], color='blue', marker='o', label='Clase 1')
plt.scatter(x1[clases == -1], x2[clases == -1], color='red', marker='x', label='Clase -1')
#Generamos dos puntos x para trazar la línea
y_linea = w[0]/w[2] - w[1]/w[2]*x1
plt.plot(x1, y_linea, color='green', linestyle='-', label='Frontera')
plt.legend()
plt.show()


