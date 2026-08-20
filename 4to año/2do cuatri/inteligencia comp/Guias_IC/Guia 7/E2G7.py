import numpy as np
import pandas as pd
import time
import matplotlib.pyplot as plt

# Ejercicio 2 - Guía 7
# Colonia de hormigas para Agente viajero

# Cargar matriz de distancias (archivo gr17.csv)
# Cada D_pq representa la distancia entre ciudad p y ciudad q
# El archivo es una matriz cuadrada n x n

D = pd.read_csv("gr17.csv", header=None).values
n = D.shape[0]  # numero de ciudades

# Funciones auxiliares

def calcular_longitud(ruta, distancias):
    return sum(distancias[ruta[i], ruta[(i+1) % len(ruta)]] for i in range(len(ruta)))

# ciudad_actual: índice de la ciudad actual "i"
# ciudades_no_visitadas: lista de índices de ciudades no visitadas "j"
# feromonas: matriz de feromonas ij
# eta: matriz de conocimiento (1/distancia) ij
# alpha, beta: parámetros que ponderan la influencia de feromonas y eta (sus exponentes)
def probabilidad_transicion(ciudad_actual, ciudades_no_visitadas, feromonas, eta, alpha, beta):
    feromonas_vals = feromonas[ciudad_actual, ciudades_no_visitadas] ** alpha
    eta_vals = eta[ciudad_actual, ciudades_no_visitadas] ** beta
    probs = feromonas_vals * eta_vals
    return probs / np.sum(probs)

# Algoritmo de Colonia de Hormigas 
def colonia_hormigas(
    D,
    n_hormigas=20,
    iteraciones=100,
    alpha=1.0,
    beta=5.0,
    rho=0.5, # tasa de evaporación
    feromonas_inicial=1.0,
    metodo="global",  # "global", "local" o "uniforme"
    semilla=0
):
    np.random.seed(semilla)
    n = D.shape[0]
    feromonas = np.ones((n, n)) * feromonas_inicial     # matriz de feromonas
    eta = 1 / (D + np.eye(n))               # visibilidad o conocimiento (1/distancia)
    
    mejor_ruta_global = None
    mejor_longitud_global = np.inf
    historia_mejor = []
    
    t0 = time.time()
    evaluaciones = 0

    for it in range(iteraciones):
        rutas = []
        longitudes = []
        
        # Soluciones por cada hormiga 
        for k in range(n_hormigas):
            ruta = [np.random.randint(0, n)] # ciudad inicial aleatoria
            while len(ruta) < n: # creiterio que me asegura que visite todas las ciudades y vuelta a la inicial.
                ciudad_actual = ruta[-1] # ciudad actual
                ciudades_no_visitadas = list(set(range(n)) - set(ruta)) # ciudades no visitadas
                p = probabilidad_transicion(ciudad_actual, ciudades_no_visitadas, feromonas, eta, alpha, beta) # llamo a la funcion de probabilidad
                siguiente = np.random.choice(ciudades_no_visitadas, p=p) # elijo la siguiente ciudad según la probabilidad
                ruta.append(siguiente)
            rutas.append(ruta)
            longitud = calcular_longitud(ruta, D)
            longitudes.append(longitud)
            evaluaciones += 1
        
        # Actualización del mejor global
        idx_mejor_iter = np.argmin(longitudes)
        if longitudes[idx_mejor_iter] < mejor_longitud_global:
            mejor_longitud_global = longitudes[idx_mejor_iter]
            mejor_ruta_global = rutas[idx_mejor_iter].copy()
        
        historia_mejor.append(mejor_longitud_global)
        
        # Actualización de feromonas
        feromonas *= (1 - rho)  # evaporación formuala

        if metodo == "global":
            # Solo la mejor hormiga global deposita feromona
            for i in range(n):
                a, b = mejor_ruta_global[i], mejor_ruta_global[(i+1)%n] 
                feromonas[a, b] += 1.0 / mejor_longitud_global
                feromonas[b, a] = feromonas[a, b] # matriz simétrica

        elif metodo == "local":
            # Todas las hormigas depositan según su longitud
            for k in range(n_hormigas):
                for i in range(n):
                    a, b = rutas[k][i], rutas[k][(i+1)%n]
                    feromonas[a, b] += 1.0 / longitudes[k]
                    feromonas[b, a] = feromonas[a, b] # matriz simétrica

        elif metodo == "uniforme":
            # Depósito igual por cada hormiga, sin depender de la longitud
            for k in range(n_hormigas):
                for i in range(n):
                    a, b = rutas[k][i], rutas[k][(i+1)%n]
                    feromonas[a, b] += feromonas_inicial
                    feromonas[b, a] = feromonas[a, b] # matriz simétrica
        
    tiempo = time.time() - t0

    return mejor_ruta_global, mejor_longitud_global, historia_mejor, tiempo, evaluaciones


# Experimentos con distintas configuraciones

configuraciones = [
    {"metodo": "global", "rho": 0.3, "feromonas_inicial": 1.0},
    {"metodo": "global", "rho": 0.7, "feromonas_inicial": 1.0},
    {"metodo": "local",  "rho": 0.5, "feromonas_inicial": 1.0},
    {"metodo": "uniforme","rho": 0.5, "feromonas_inicial": 0.1},
]

resultados = []

for conf in configuraciones:
    ruta, longitud, hist, t, evals = colonia_hormigas(
        D, 
        n_hormigas=20,
        iteraciones=100,
        rho=conf["rho"],
        feromonas_inicial=conf["feromonas_inicial"],
        metodo=conf["metodo"]
    )
    resultados.append({
        "Método": conf["metodo"],
        "ρ": conf["rho"],
        "Feromona inicial": conf["feromonas_inicial"],
        "Longitud mínima": round(longitud, 3),
        "Tiempo (s)": round(t, 3),
        "Evaluaciones": evals
    })
    plt.plot(hist, label=f"{conf['metodo']} (ρ={conf['rho']})")


# Resultados y tabla comparativa
plt.xlabel("Iteración")
plt.ylabel("Mejor longitud encontrada")
plt.title("Convergencia de la Colonia de Hormigas ")
plt.legend()
plt.grid(True)
plt.show()

tabla_resultados = pd.DataFrame(resultados)
print("\n TABLA COMPARATIVA DE RESULTADOS ")
print(tabla_resultados)

