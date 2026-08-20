import numpy as np
import matplotlib.pyplot as plt

# Guia 6 Ejercicio 1.2
# Comparación Algoritmo Genético vs Gradiente Descendente

# Definición de la función objetivo 2D
def f2(xy):
    x, y = xy
    r2 = x**2 + y**2
    return (r2**0.25) * (np.sin(50 * (r2**0.1))**2 + 1)


# Gradiente numérico en 2D (aproximación por diferencias finitas)
def gradiente_numerico(xy, h=1e-5):
    x, y = xy
    grad_x = (f2([x + h, y]) - f2([x - h, y])) / (2*h)
    grad_y = (f2([x, y + h]) - f2([x, y - h])) / (2*h)
    return np.array([grad_x, grad_y])


# Algoritmo Genético 2D
def algoritmo_genetico_2D(
    poblacion_size=100,
    generaciones=2000,
    dominio=(-100, 100),
    prob_cruza=0.8,
    prob_mutacion=0.2
):
    poblacion = np.random.uniform(dominio[0], dominio[1], (poblacion_size, 2))
    
    mejor_individuo = None
    mejor_valor = np.inf
    
    for gen in range(generaciones):
        valores = np.array([f2(ind) for ind in poblacion])
        
        idx_best = np.argmin(valores)
        if valores[idx_best] < mejor_valor:
            mejor_valor = valores[idx_best]
            mejor_individuo = poblacion[idx_best].copy()
        
        # Selección por torneo
        padres = []
        for _ in range(poblacion_size):
            i1, i2 = np.random.randint(0, poblacion_size, 2)
            padres.append(poblacion[i1] if valores[i1] < valores[i2] else poblacion[i2])
        padres = np.array(padres)
        
        # Cruza lineal
        hijos = []
        for i in range(0, poblacion_size, 2):
            p1, p2 = padres[i], padres[i+1]
            if np.random.rand() < prob_cruza:
                alpha = np.random.rand()
                h1 = alpha * p1 + (1 - alpha) * p2
                h2 = alpha * p2 + (1 - alpha) * p1
            else:
                h1, h2 = p1.copy(), p2.copy()
            hijos.extend([h1, h2])
        hijos = np.array(hijos)
        
        # Mutación
        for i in range(poblacion_size):
            if np.random.rand() < prob_mutacion:
                hijos[i] += np.random.normal(0, 2, size=2)
                hijos[i] = np.clip(hijos[i], dominio[0], dominio[1])
        
        poblacion = hijos
    
    return mejor_individuo, mejor_valor


# Gradiente Descendente 2D
def gradiente_descendente_2D(
    lr=0.05,
    max_iter=2000,
    dominio=(-100, 100)
):
    # Punto inicial aleatorio
    xy = np.random.uniform(dominio[0], dominio[1], 2)
    mejor_xy, mejor_valor = xy.copy(), f2(xy)
    
    for _ in range(max_iter):
        grad = gradiente_numerico(xy)
        xy = xy - lr * grad
        xy = np.clip(xy, dominio[0], dominio[1])  # Mantener dentro del dominio
        
        valor = f2(xy)
        if valor < mejor_valor:
            mejor_valor = valor
            mejor_xy = xy.copy()
    
    return mejor_xy, mejor_valor


# Main y comparación
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
