import csv
import numpy as np
import matplotlib.pyplot as plt
# Guia 2 - Ejercicio 1

# Datos de Entrenamiento
datos_entrada = []
datos_salidas = []

np.random.seed(0) # Para que siempre genere los mismos pesos aleatorios.

# Funcion de activacion sigmoide (simétrica) f(x) = 2 / (1 + exp(-x)) - 1
# Retorna valores en [-1, 1].
def sigmoide(x):
    return 2 / (1 + np.exp(-x)) - 1

# Derivada de la sigmoide simétrica respecto de su salida y: f'(y) = 0.5 * (1+y) * (1-y)
def sigmoide_derivada(y):
    return 0.5 * (1 + y) * (1 - y)


# Clase Capa
class Capa:
    def __init__(self, n_entradas, n_neuronas):
        """
        n_entradas: número de entradas de la capa
        n_neuronas: número de neuronas en esta capa
        self.pesos: matriz de pesos de tamaño (n_neuronas x n_entradas + 1)
                    pesos[i,j] = peso de la conexión de la entrada j hacia la neurona i
        """
   
        self.pesos = np.random.uniform(-0.5, 0.5, (n_neuronas, n_entradas+1)) # +1 PARA EL BIAS 
        self.salida = None    # vector de salida de esta capa (tamaño n_neuronas,)
        self.delta = None     # vector de deltas (gradientes locales)
        self.entradas = None  # vector de entradas recibido (n_entradas)
    def forward(self, entradas):
        entradas = np.hstack(([-1], entradas))   # agregar bias x0 = -1
        self.entradas = entradas
        z = np.dot(self.pesos, entradas)   # z_i = Σ w_ij * x_j
        self.salida = sigmoide(z)
        return self.salida # Salida de la capa, vector (n_neuronas)

    def calcular_delta_salida(self, yd):
        """
        Cálculo del delta en la capa de salida (δ_iii en el apunte):
        δ_i = (y_d - y_i) * f'(y_i)
        -> ver que desde esta capa se propaga el error (y_d - y) hacia atras...
        """
        self.delta = (yd - self.salida) * sigmoide_derivada(self.salida)

    def calcular_delta_oculta(self, pesos_siguiente, delta_siguiente):
        """
        Cálculo del delta en capas ocultas:
        δ_i = f'(y_i) * Σ δ_k * w_ki para cada neurona de la capa siguiente 
        donde:
          - pesos_siguiente: matriz (n_neuronas_siguiente x n_neuronas_actual)
          - delta_siguiente: vector (n_neuronas_siguiente,)
        Si estoy en la capa i , necesito los pesos w_(i+1) y los deltas_(i+1) 
        """
        self.delta = np.dot(pesos_siguiente[:, 1:].T, delta_siguiente) * sigmoide_derivada(self.salida) 
        # pesos_siguiente[:, 1:] para descartar los pesos del bias de la capa siguiente

    def actualizar_pesos(self, tasa_aprendizaje):
        # Actualización de pesos: Δw_ij = ta * δ_i * x_j
        entradas = self.entradas.reshape(1, -1)   # (1 x n_entradas) entradas_traspuesta [-1, x1, x2]   
        delta = self.delta.reshape(-1, 1)         # (n_neuronas x 1) [d1,d2,d3]'T
        self.pesos += tasa_aprendizaje * np.dot(delta, entradas)  # (n_neuronas x n_entradas)

        #Aca lo que hace es transponer un vector para luego hacer el producto punto entre delta asi [ d1,d2,d3]^t * [x1,x2,x3] 
        #Eso nos va a dar una matriz exactamente de igual dimension que la de los pesos, para asi lograr una suma de matrices de igual dimension


# Clase Perceptrón Multicapa (MLP)
class MLP:
    def __init__(self, estructura, tasa_aprendizaje=0.1, max_epocas=10000):
        """
        estructura: lista con nº de neuronas por capa. Ej: [2, 2, 1]
            -> cantidad de entradas: 2 entradas
            -> capa oculta: 2 neuronas
            -> cantidad de salidas: 1 neurona
        otro ej: red = MLP(estructura=[4, 5, 4, 2], tasa_aprendizaje=0.1, max_epocas=100)
        que son 4 entradas, capa de entrada 5 neuronas, capa oculta de 4 neuronas y capa de salida de 2 neuronas y salidas.
        """
        self.capas = []
        self.tasa = tasa_aprendizaje
        self.max_epocas = max_epocas

        for i in range(1, len(estructura)): # Empezamos en 1 porque la capa 0 es la de entradas, no es una capa con neuronas.
            # Creamos cada capa con sus pesos aleatorios
            self.capas.append(Capa(estructura[i-1], estructura[i]))

    def forward(self, patron): # x1,x2
        # Realiza la propagación hacia adelante de un patrón.
        salida = patron
        for capa in self.capas:
            salida = capa.forward(salida) # la salida de una capa es la entrada de la siguiente.
        return salida

    def train(self, X, Y):
        """
        Entrenamiento con retropropagación.
        X: matriz de patrones de entrada (n_patrones x n_entradas)
        Y: matriz de salidas deseadas (n_patrones x n_salidas)
        """
        for epoca in range(self.max_epocas):
            error_total = 0
            print(f"Época {epoca}")
            for x, y in zip(X, Y):
                # FORWARD
                salida = self.forward(x) # salida y de la red para el patrón x

                # BACKWARD

                # Delta en capa de salida
                self.capas[-1].calcular_delta_salida(y) # a la ultima capa le calculamos el delta de forma distinta.

                # Delta en capas ocultas (desde la penúltima hasta la primera)
                for i in reversed(range(len(self.capas)-1)):
                    self.capas[i].calcular_delta_oculta(self.capas[i+1].pesos, self.capas[i+1].delta)
                # Acordarse que aca para calcular el delta de una capa i, necesitamos los pesos y deltas de la capa siguiente ii.

                # Actualización de pesos
                for capa in self.capas:
                    capa.actualizar_pesos(self.tasa)

    def predecir(self, X):
        # Realiza predicciones para un conjunto de entradas.
        Y = []
        for x in X: # cada patrón de entrada
            salida = self.forward(x)
            Y.append(salida)
        return np.array(Y)


def leer_archivo(nombre):
    with open(nombre, mode='r', encoding='utf-8') as archivo:
    #with open(r"C:\Users\adri\Desktop\IC\Guia 2\XOR_trn.csv", mode='r', encoding='utf-8') as archivo:
        lector = csv.reader(archivo)
    
        for fila in lector:
            x1, x2, yd = map(float, fila)
            datos_entrada.append([x1, x2])  # Ya no agregamos el bias aca, lo hace la capa automáticamente.
            datos_salidas.append(yd) # Y_deseada

    # Convertir a matrices de NumPy
    X = np.array(datos_entrada)
    Y = np.array(datos_salidas).reshape(-1, 1)  # <- forma (n_patrones, 1)
    return X, Y

def main():
    # Definir la estructura de la red
    # Abrimos y leemos el archivo, guardamos los valores en los vectores entradas y salidas.
    X, Y = leer_archivo('XOR_trn.csv')
    # Crear y entrenar la red
    red = MLP(estructura=[2,2,1], tasa_aprendizaje=0.01, max_epocas=100)
    red.train(X, Y) # Entrenamiento de la red con los datos XOR para obtener los pesos.

    X_test, Y_test = leer_archivo('XOR_tst.csv')
    # Prueba final
    print("\nPrueba XOR:")
    aciertos = 0
    total = len(X_test)
    for x, y in zip(X_test, Y_test):    
        salida = red.forward(x)
        prediccion = np.round(salida)  # Redondea la salida para clasificación binaria
        print(f"Entrada: {x}, Esperado: {y}, Predicción: {np.round(salida, 3)}")
        if np.array_equal(prediccion, y): # si la prediccion es igual a la salida deseada.
            aciertos += 1
    tasa_aciertos = aciertos / total
    print(f"\nTasa de aciertos: {tasa_aciertos * 100:.2f}%")

# Obtener los pesos de la capa 1 (dos neuronas) y capa 2 (una neurona)
    pesos_capa1 = red.capas[0].pesos  # (2 neuronas x 3 pesos)
    pesos_capa2 = red.capas[1].pesos  # (1 neurona x 3 pesos)

    xs = np.linspace(-5, 5, 500)

    plt.figure(figsize=(8,6))
    # Graficar puntos
    for i in range(len(X)):
        if Y[i] == 1:
            plt.scatter(X[i][0], X[i][1], color="blue", marker="o", label="Clase 1" if i == 0 else "")
        else:
            plt.scatter(X[i][0], X[i][1], color="red", marker="x", label="Clase -1" if i == 0 else "")

    # Graficar rectas de las neuronas de la capa 1
    colores = ["green", "purple"]    
    for idx in range(2): # para cada neurona de la capa 1
        w0, w1, w2 = pesos_capa1[idx]
        ys = (w0 - w1*xs)/w2
        plt.plot(xs, ys, color=colores[idx], label=f"Neurona {chr(97+idx)} (Capa 1)")
        print(idx)
    plt.xlim(-5, 5)
    plt.ylim(-5, 5)
    plt.xlabel("x1")
    plt.ylabel("x2")
    plt.legend()
    plt.title("Fronteras de decisión de las neuronas (XOR)")
    plt.grid(True)
    plt.show()



    salidas_ocultas = []
    for x in X:
        # Propagación hasta la capa oculta
        salida_oculta = red.capas[0].forward(x)
        salidas_ocultas.append(salida_oculta)

    salidas_ocultas = np.array(salidas_ocultas)  # (n_patrones, n_neuronas_ocultas)

    # Graficar las salidas de la anteúltima capa (capa oculta)
    plt.figure(figsize=(8,6))
    colores = ["green", "purple"]
    for i in range(len(X)):
        if Y[i] == 1:
            plt.scatter(salidas_ocultas[i][0], salidas_ocultas[i][1], color="blue", marker="o", label="Clase 1" if i == 0 else "")
        else:
            plt.scatter(salidas_ocultas[i][0], salidas_ocultas[i][1], color="red", marker="x", label="Clase -1" if i == 0 else "")
    
    w0, w1, w2 = pesos_capa2[0]
    xs = np.linspace(-5, 5, 500)
    ys = (w0 - w1*xs)/w2
    plt.plot(xs, ys, color="red", label="Frontera de decisión (Capa 2)")
    plt.title("Salidas de la anteúltima capa (oculta) para cada entrada")
    plt.xlabel("x1")
    plt.ylabel("x2")
    plt.xlim(-5, 5)
    plt.ylim(-5, 5)
    plt.grid(True)
    plt.legend()
    plt.show()
main() 
