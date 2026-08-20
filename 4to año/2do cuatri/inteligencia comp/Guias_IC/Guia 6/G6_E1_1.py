import numpy as np
import matplotlib.pyplot as plt

# Guia 6 - Ejercicio 1.1

# Definición de la función objetivo
# f(x) = -x * sin(sqrt(|x|)), con x en [-512, 512]

def f(x):
    return -x * np.sin(np.sqrt(np.abs(x)))

# Derivada analítica de f(x) para gradiente descendente
def f_derivada(x):
    if x == 0:  # Evitamos división por cero
        return 0
    return -np.sin(np.sqrt(np.abs(x))) - (x * np.cos(np.sqrt(np.abs(x)))) / (2 * np.sqrt(np.abs(x)))



# Decodificación binario a real
# individuo : array de 0/1
# dominio   : (xmin, xmax)
# n_bits    : número de bits usados para representar la variable


def decode(individuo, dominio, n_bits):
    # Convertimos la cadena binaria a un entero
    valor_entero = 0
    for bit in individuo:
        valor_entero = (valor_entero << 1) | bit  # shift + OR
    
    # Escalamos linealmente al dominio real
    xmin, xmax = dominio
    real = xmin + (valor_entero / (2**n_bits - 1)) * (xmax - xmin) # OJO
    return real


# Algoritmo Genético
def algoritmo_genetico(
    poblacion_size=30,   # Número de individuos en la población
    generaciones=200,    # Número de iteraciones
    n_bits=16,           # Número de bits para representar la variable x
    dominio=(-512, 512), # Rango de búsqueda
    prob_cruza=0.8,      # Probabilidad de cruzamiento
    prob_mutacion=0.01   # Probabilidad de mutación (flip de bit)
):
    # Inicialización
    # Creamos una población aleatoria en numero binario de 0s y 1s 
    poblacion = np.random.randint(0, 2, (poblacion_size, n_bits))
    
    mejor_individuo = None
    mejor_valor = np.inf

    # Iteraciones-generaciones
    for gen in range(generaciones):
        
        # Decodificamos y evaluamos cada individuo
        valores = np.array([f(decode(ind, dominio, n_bits)) for ind in poblacion])
        
        # Guardamos el mejor de la generación
        idx_best = np.argmin(valores) # índice del mejor fitness
        if valores[idx_best] < mejor_valor:
            mejor_valor = valores[idx_best]
            mejor_individuo = poblacion[idx_best].copy()
        
        # Selección por competencia (Tournament selection)
        padres = []
        for _ in range(poblacion_size):
            i1, i2 = np.random.randint(0, poblacion_size, 2)
            if valores[i1] < valores[i2]:
                padres.append(poblacion[i1])
            else:
                padres.append(poblacion[i2])
        padres = np.array(padres)
        
        # Cruza de un punto
        hijos = []
        for i in range(0, poblacion_size, 2):
            p1, p2 = padres[i], padres[i+1]
            if np.random.rand() < prob_cruza:
                punto = np.random.randint(1, n_bits-1) # punto de corte
                h1 = np.concatenate([p1[:punto], p2[punto:]])
                h2 = np.concatenate([p2[:punto], p1[punto:]])
            else:
                h1, h2 = p1.copy(), p2.copy()
            hijos.extend([h1, h2])
        hijos = np.array(hijos)
        
        # Mutación cambia de bit con baja probabilidad 
        for ind in hijos:
            for j in range(n_bits):
                if np.random.rand() < prob_mutacion:
                    ind[j] = 1 - ind[j]  # flip bit (0a 1, 1a0)
        
        # Nueva población = hijos
        poblacion = hijos
    
    # Al terminar devolvemos el mejor individuo decodificado
    mejor_x = decode(mejor_individuo, dominio, n_bits)
    return mejor_x, mejor_valor

# Gradiente Descendente 1D
def gradiente_descendente(
    lr=0.1,                # Tasa de aprendizaje
    max_iter=1000,         # Número máximo de iteraciones
    dominio=(-512, 512)    # Rango de búsqueda
):
    # Punto inicial aleatorio dentro del dominio
    x = np.random.uniform(dominio[0], dominio[1])
    mejor_x, mejor_valor = x, f(x)
    
    for _ in range(max_iter):
        grad = f_derivada(x)
        x = x - lr * grad
        x = np.clip(x, dominio[0], dominio[1])  # Mantener dentro del dominio
        
        valor = f(x)
        if valor < mejor_valor:
            mejor_valor = valor
            mejor_x = x
    
    return mejor_x, mejor_valor


# Main, graficos y resultados
if __name__ == "__main__":
    # Algoritmo Genético
    mejor_x_ag, mejor_f_ag = algoritmo_genetico()
    print(f"[AG] Mejor solución encontrada: x = {mejor_x_ag:.5f}, f(x) = {mejor_f_ag:.5f}")
    
    # Gradiente Descendente
    mejor_x_gd, mejor_f_gd = gradiente_descendente()
    print(f"[GD] Mejor solución encontrada: x = {mejor_x_gd:.5f}, f(x) = {mejor_f_gd:.5f}")
    
    # Graficamos la función y los mínimos encontrados
    xs = np.linspace(-512, 512, 1000)
    ys = f(xs)
    
    plt.figure(figsize=(10,5))
    plt.plot(xs, ys, label="f(x)")
    plt.scatter(mejor_x_ag, mejor_f_ag, color="red", label="Mínimo AG")
    plt.scatter(mejor_x_gd, mejor_f_gd, color="green", label="Mínimo GD")
    plt.title("Optimización con Algoritmo Genético vs Gradiente Descendente (1D)")
    plt.xlabel("x")
    plt.ylabel("f(x)")
    plt.legend()
    plt.grid(True)
    plt.show()
