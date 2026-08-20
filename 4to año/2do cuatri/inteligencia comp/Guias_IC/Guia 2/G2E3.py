import csv
import numpy as np
import matplotlib.pyplot as plt
# Guia 2 - Ejercicio 3

# Datos de Entrenamiento
datos_entrada = []
datos_salidas = []


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
        self.pesos: matriz de pesos de tamaño (n_neuronas x n_entradas)
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
        δ_i = f'(y_i) * Σ δ_k * w_ki
        donde:
          - pesos_siguiente: matriz (n_neuronas_siguiente x n_neuronas_actual)
          - delta_siguiente: vector (n_neuronas_siguiente,)
        Si estoy en la capa i , necesito los pesos w_(i+1) y los deltas_(i+1) 
        """
        self.delta = np.dot(pesos_siguiente[:, 1:].T, delta_siguiente) * sigmoide_derivada(self.salida) 
        # pesos_siguiente[:, 1:] para descartar los pesos del bias de la capa siguiente

    def actualizar_pesos(self, tasa_aprendizaje):
        # Actualización de pesos: Δw_ij = ta * δ_i * x_j
        entradas = self.entradas.reshape(1, -1)   # (1 x n_entradas) entradas_traspuesta
        delta = self.delta.reshape(-1, 1)         # (n_neuronas x 1)
        self.pesos += tasa_aprendizaje * np.dot(delta, entradas)  # (n_neuronas x n_entradas)


# Clase Perceptrón Multicapa (MLP)
class MLP:
    def __init__(self, estructura, tasa_aprendizaje=0.1, max_epocas=10000):
        """
        estructura: lista con nº de neuronas por capa. Ej: [2, 2, 1]
            -> capa entrada: 2 entradas
            -> capa oculta: 2 neuronas
            -> capa salida: 1 neurona
        otro ej: red = MLP(estructura=[4, 5, 4, 2], tasa_aprendizaje=0.1, max_epocas=100)
        que son 4 entradas, capa de entrada 5 neuronas, capa oculta de 4 neuronas y capa de salida de 2 neuronas y salidas.
        """
        self.capas = []
        self.tasa = tasa_aprendizaje
        self.max_epocas = max_epocas

        for i in range(1, len(estructura)): # Empezamos en 1 porque la capa 0 es la de entradas, no es una capa con neuronas.
            # Creamos cada capa con sus pesos aleatorios
            self.capas.append(Capa(estructura[i-1], estructura[i]))

    def forward(self, patron):
        # Realiza la propagación hacia adelante de un patrón.
        salida = patron
        for capa in self.capas:
            salida = capa.forward(salida) # la salida de una capa es la entrada de la siguiente.
        return salida

    def train(self, X, Y):
        """
        Entrenamiento con retropropagación, reportando desempeño por época.
        """
        history = {"acc": [], "ecm": []}  # historial de errores

        for epoca in range(self.max_epocas):
            aciertos = 0
            error_total = 0
            for x, y in zip(X, Y):
                # FORWARD
                salida = self.forward(x)

                # BACKWARD
                self.capas[-1].calcular_delta_salida(y)
                for i in reversed(range(len(self.capas)-1)):
                    self.capas[i].calcular_delta_oculta(self.capas[i+1].pesos, self.capas[i+1].delta)

                for capa in self.capas:
                    capa.actualizar_pesos(self.tasa)

                # Error cuadrático medio por patrón
                error_total += np.mean((y - salida)**2)

                # conteo de aciertos (clasificación)
                pos_pred = np.argmax(salida)
                salida_clase = np.ones_like(salida)*-1
                salida_clase[pos_pred] = 1
                if np.array_equal(salida_clase, y):
                    aciertos += 1

            # promedios de la época
           
            tasa_aciertos = aciertos / len(X)
            error_total /= len(X)
           
            history["acc"].append(tasa_aciertos)
            history["ecm"].append(error_total)

            print(f"Época {epoca+1}: Aciertos={tasa_aciertos*100:.2f}%, ECM={error_total:.4f}")


        return history


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
            x1, x2, x3, x4, yd0, yd1, yd2 = map(float, fila)
            datos_entrada.append([x1, x2, x3, x4])  # Ya no agregamos el bias aca, lo hace la capa automáticamente.
            datos_salidas.append([yd0, yd1, yd2])  # Y_deseada

    # Convertir a matrices de NumPy
    X = np.array(datos_entrada)
    Y = np.array(datos_salidas).reshape(-1, 3)  # <- forma (n_patrones, 1)
    return X, Y

def main():
    # Datos de entrenamiento
    X, Y = leer_archivo('iris81_trn.csv')

    # Crear y entrenar
    # red = MLP(estructura=[4,5,5,3], tasa_aprendizaje=0.001, max_epocas=2000) anda bien con
    # Entrenamiento aciertos del 99.10% y en test 99.97%. 
    red = MLP(estructura=[4,5,5,3], tasa_aprendizaje=0.001, max_epocas=3000)
    history = red.train(X, Y)

    # Evaluación en test
    X_test, Y_test = leer_archivo('iris81_tst.csv')
    aciertos = 0
    total = len(X_test)
    for x, y in zip(X_test, Y_test):
        salida = red.forward(x)
        pos_pred = np.argmax(salida)
        salida = np.ones_like(salida)*-1
        salida[pos_pred] = 1

        # print(f"Entrada: {x}, Esperado: {y}, Predicción: {np.round(salida, 3)}")
        if np.array_equal(salida, y):
            aciertos += 1
    tasa_aciertos = aciertos / total
    print(f"\nTasa de aciertos (TEST): {tasa_aciertos * 100:.2f}%")

    plt.figure(figsize=(8,5))
    plt.plot(history["acc"], label="Precisión del entrenamiento")
    plt.plot(history["ecm"], label="ECM del entrenamiento")  # <-- Añade esta línea
    plt.xlabel("Epoca")
    plt.ylabel("Precisión / ECM")
    plt.title("Evolución de la tasa de aciertos y ECM")
    plt.legend()
    plt.grid(True)
    plt.show()



main()
