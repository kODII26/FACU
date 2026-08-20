import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

def funcActivacion(result):
    return 1 if result >= 0 else -1

# Leer CSV sin encabezado
data_train = pd.read_csv("OR_trn.csv", header=None)
data_test = pd.read_csv("OR_tst.csv", header=None)

# Columnas de entrenamiento
x1train = data_train.iloc[:, 0].to_numpy()
x2train = data_train.iloc[:, 1].to_numpy()
ytrain = data_train.iloc[:, 2].to_numpy()
colx0_train = np.full(len(x1train), -1)

# Pesos iniciales
w0 = 0.35  
w1 = 0.35
w2 = 0.35
gamma = 0.01
epocas = 3

# --- Graficar puntos ---
plt.figure(figsize=(8, 6))
plt.scatter(x1train, x2train, c=-ytrain, cmap='bwr', edgecolor='k', label='Train')

# --- Entrenamiento con graficado de rectas ---
total_iters = epocas * len(x1train)
iter_count = 0

for epoca in range(epocas):
    for i in range(len(x1train)):
        # Predicción lineal
        y_lin = funcActivacion(w0 * colx0_train[i] + w1 * x1train[i] + w2 * x2train[i])
        
        # Error
        error = ytrain[i] - y_lin
        
        # Actualización de pesos
        w0 += gamma * error * colx0_train[i]
        w1 += gamma * error * x1train[i]
        w2 += gamma * error * x2train[i]
        
        # Graficar la recta actual
        x_vals = np.linspace(-2, 2, 100)
        y_vals = (w0 - w1 * x_vals) / w2
        alpha = (iter_count + 1) / total_iters  # opacidad creciente
        plt.plot(x_vals, y_vals, color='black', alpha=alpha)
        
        iter_count += 1

plt.xlabel("x1")
plt.ylabel("x2")
plt.title("Evolución de la frontera de decisión")
plt.grid(True)
plt.legend()
plt.show()
