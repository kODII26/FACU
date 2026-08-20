import numpy as np
import matplotlib.pyplot as plt

# Guia 6 - Ejercicio 1.2 

# Definición de la función objetivo 2D
# f(x,y) = (x^2+y^2)^0.25 * (sin^2(50(x^2+y^2)^0.1) + 1)
def f2(x, y):
    r2 = x**2 + y**2
    return (r2**0.25) * (np.sin(50 * (r2**0.1))**2 + 1)

# Gradiente numérico en 2D (aproximación por diferencias finitas)
def gradiente_numerico(xy, h=1e-5):
    x, y = xy
    grad_x = (f2(x + h, y) - f2(x - h, y)) / (2*h)
    grad_y = (f2(x, y + h) - f2(x, y - h)) / (2*h)
    return np.array([grad_x, grad_y])


# Decodificación binario a real
# individuo : array de 0/1 (longitud 2*n_bits)
# dominio   : (xmin, xmax)
# n_bits    : número de bits por variable
# return    : (x, y) en el dominio real
def decode(individuo, dominio, n_bits):
    # Primera mitad = x, segunda mitad = y
    bits_x = individuo[:n_bits]
    bits_y = individuo[n_bits:]
    
    # Binario a entero
    def binario_a_real(bits):
        valor_entero = 0
        for bit in bits:
            valor_entero = (valor_entero << 1) | bit # shift + OR
        xmin, xmax = dominio
        return xmin + (valor_entero / (2**n_bits - 1)) * (xmax - xmin) # OJO
    
    x = binario_a_real(bits_x)
    y = binario_a_real(bits_y)
    return x, y


# Algoritmo Genético 2D
def algoritmo_genetico_2D(
    poblacion_size=30,   # Número de individuos
    generaciones=300,    # Número de iteraciones
    n_bits=12,           # Bits por variable
    dominio=(-100, 100), # Dominio de búsqueda
    prob_cruza=0.8,      # Probabilidad de cruza
    prob_mutacion=0.01   # Probabilidad de mutación
):
    # Un individuo ahora tiene 2*n_bits bits
    long_cromosoma = 2 * n_bits
    
    # Población inicial aleatoria
    poblacion = np.random.randint(0, 2, (poblacion_size, long_cromosoma))
    
    mejor_individuo = None
    mejor_valor = np.inf
    
    # Iteraciones-generaciones
    for gen in range(generaciones):
        
        # Decodificar y evaluar
        valores = []
        for ind in poblacion:
            x, y = decode(ind, dominio, n_bits)
            valores.append(f2(x, y))
        valores = np.array(valores)
        
        # Guardar mejor
        idx_best = np.argmin(valores) # índice del mejor fitness
        if valores[idx_best] < mejor_valor:
            mejor_valor = valores[idx_best]
            mejor_individuo = poblacion[idx_best].copy()
        
        # Selección por competencia
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
                punto = np.random.randint(1, long_cromosoma-1) # punto de cruza aleatorio
                h1 = np.concatenate([p1[:punto], p2[punto:]])
                h2 = np.concatenate([p2[:punto], p1[punto:]])
            else:
                h1, h2 = p1.copy(), p2.copy()
            hijos.extend([h1, h2])
        hijos = np.array(hijos)
        
        # Mutación (flip de bits)
        for ind in hijos:
            for j in range(long_cromosoma):
                if np.random.rand() < prob_mutacion:
                    ind[j] = 1 - ind[j]
        
        # Nueva población
        poblacion = hijos
    
    # Mejor solución final
    mejor_x, mejor_y = decode(mejor_individuo, dominio, n_bits)
    return (mejor_x, mejor_y), mejor_valor

def gradiente_descendente_2D(
    lr=0.05,
    max_iter=2000,
    dominio=(-100, 100)
):
    # Punto inicial aleatorio
    xy = np.random.uniform(dominio[0], dominio[1], 2)
    mejor_xy, mejor_valor = xy.copy(), f2(*xy)
    
    for _ in range(max_iter):
        grad = gradiente_numerico(xy)
        xy = xy - lr * grad
        xy = np.clip(xy, dominio[0], dominio[1])  # Mantener dentro del dominio
        
        valor = f2(*xy)
        if valor < mejor_valor:
            mejor_valor = valor
            mejor_xy = xy.copy()
    
    return mejor_xy, mejor_valor

# Main, graficos y resultados
if __name__ == "__main__":
    # Algoritmo Genético
    mejor_xy_ag, mejor_f_ag = algoritmo_genetico_2D()
    print(f"[AG] Mejor solución encontrada: (x, y) = {mejor_xy_ag}, f(x,y) = {mejor_f_ag:.5f}")
    
    # Gradiente Descendente
    mejor_xy_gd, mejor_f_gd = gradiente_descendente_2D()
    print(f"[GD] Mejor solución encontrada: (x, y) = {mejor_xy_gd}, f(x,y) = {mejor_f_gd:.5f}")
    
    # Graficamos la función con un mapa de colores
    X = np.linspace(-100, 100, 300)
    Y = np.linspace(-100, 100, 300)
    XX, YY = np.meshgrid(X, Y)
    Z = (XX**2 + YY**2)**0.25 * (np.sin(50*(XX**2+YY**2)**0.1)**2 + 1)

    plt.figure(figsize=(10,6))
    plt.contourf(XX, YY, Z, levels=100, cmap="jet")
    plt.colorbar(label="f(x,y)")
    plt.scatter(mejor_xy_ag[0], mejor_xy_ag[1], color="red", label="Mínimo AG")
    plt.scatter(mejor_xy_gd[0], mejor_xy_gd[1], color="green", label="Mínimo GD")
    plt.title("Optimización con Algoritmo Genético vs Gradiente Descendente (2D)")
    plt.xlabel("x")
    plt.ylabel("y")
    plt.legend()
    plt.show()
