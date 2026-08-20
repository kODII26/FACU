import numpy as np
import matplotlib.pyplot as plt
import time

# Ejercicio 1 - Guía 7: Enjambre de Partículas (PSO)

# f1(x): función 1D
def f1(x):
    """f1(x) = -x * sin(sqrt(|x|))"""
    x = np.array(x)
    return -x * np.sin(np.sqrt(np.abs(x)))

# f2(x,y): funcion 2D
def f2(xy):
    """f2(x,y) = (x² + y²)^0.25 * [sin²(50*(x²+y²)^0.1) + 1]"""
    x, y = xy
    r2 = x**2 + y**2
    return (r2**0.25) * (np.sin(50*(r2**0.1))**2 + 1)


# ENJAMBRE DE PARTÍCULAS (PSO 1D)
# Parametros: - num_particulas: cantidad de partículas en el enjambre
#             - iteraciones: número de ciclos de actualización maximo
#             - dominio: rango [xmin, xmax] donde buscar
#             - c1, c2: coeficientes de atracción cognitiva y social
#             - vmax_fraction: límite máximo de velocidad ( similar a tasa de aprendizaje )

# ENJAMBRE DE PARTÍCULAS (PSO 1D)
def pso_1D(num_particulas=60, iteraciones=100, dominio=(-512,512), 
           c1=1.49445, c2=1.49445, vmax_fraction=0.5, seed=0):
    
    no_mejora = 0 # contador de iteraciones sin mejora
    max_no_mejora = 30 # para parada anticipada

    np.random.seed(seed)
    xmin, xmax = dominio

    # Inicializamos posiciones aleatorias dentro del dominio
    X = np.random.uniform(xmin, xmax, size=num_particulas)
    V = np.zeros_like(X)

    pbest = X.copy()
    pbest_val = f1(X)

    g_idx = np.argmin(pbest_val)
    gbest = pbest[g_idx]
    gbest_val = float(pbest_val[g_idx])

    historia = []  
    posiciones = []   #  para guardar posiciones de cada iteración
    t0 = time.time()  
    evals = num_particulas 
    vmax = (xmax - xmin) * vmax_fraction  

    for it in range(iteraciones):
        r1 = np.random.rand(num_particulas)
        r2 = np.random.rand(num_particulas)

        V = V + c1 * r1 * (pbest - X) + c2 * r2 * (gbest - X)
        V = np.clip(V, -vmax, vmax)  

        X = X + V
        X = np.clip(X, xmin, xmax)   

        vals = f1(X)
        evals += num_particulas
        
        mejora = vals < pbest_val
        pbest[mejora] = X[mejora]
        pbest_val[mejora] = vals[mejora]

        idx = np.argmin(pbest_val)
        if pbest_val[idx] < gbest_val:
            gbest_val = float(pbest_val[idx])
            gbest = pbest[idx]
            no_mejora = 0  
        else:
            no_mejora += 1  

        historia.append(gbest_val)
        posiciones.append(X.copy())   #  guardamos las posiciones

        if no_mejora >= max_no_mejora:
            print(f"Parada anticipada en iteración {it+1} por falta de mejora.")
            break

    tiempo = time.time() - t0
    return gbest, gbest_val, historia, tiempo, evals, posiciones  # devolvemos posiciones


# ENJAMBRE DE PARTÍCULAS (PSO 2D)
def pso_2D(num_particulas=100, iteraciones=60, dominio=(-100,100), 
           c1=1.49445, c2=1.49445, vmax_fraction=0.2, seed=0):
    
    no_mejora = 0
    max_no_mejora = 30
    
    np.random.seed(seed)
    xmin, xmax = dominio
    D = 2  

    X = np.random.uniform(xmin, xmax, size=(num_particulas, D))
    V = np.zeros_like(X)

    pbest = X.copy()
    pbest_val = np.array([f2(xi) for xi in X])

    g_idx = np.argmin(pbest_val)
    gbest = pbest[g_idx].copy()
    gbest_val = float(pbest_val[g_idx])

    historia = []
    posiciones = []   #  para guardar posiciones
    t0 = time.time()
    evals = num_particulas
    vmax = (xmax - xmin) * vmax_fraction

    for it in range(iteraciones):
        r1 = np.random.rand(num_particulas, D)
        r2 = np.random.rand(num_particulas, D)

        V = V + c1 * r1 * (pbest - X) + c2 * r2 * (gbest - X)
        V = np.clip(V, -vmax, vmax)

        X = X + V
        X = np.clip(X, xmin, xmax)

        vals = np.array([f2(xi) for xi in X])
        evals += num_particulas

        mejora = vals < pbest_val
        pbest[mejora] = X[mejora]
        pbest_val[mejora] = vals[mejora]

        idx = np.argmin(pbest_val)
        if pbest_val[idx] < gbest_val:
            gbest_val = float(pbest_val[idx])
            gbest = pbest[idx]
            no_mejora = 0  
        else:
            no_mejora += 1  

        historia.append(gbest_val)
        posiciones.append(X.copy())   #  guardamos las posiciones

        if no_mejora >= max_no_mejora:
            print(f"Parada anticipada en iteración {it+1} por falta de mejora.")
            break

    tiempo = time.time() - t0
    return gbest, gbest_val, historia, tiempo, evals, posiciones  #  devolvemos posiciones


# Main
if __name__ == "__main__":
    print("=== PSO 1D ===")
    
    #  x_best  → mejor posición encontrada
    #  val_best → valor de la función en esa posición
    #  hist → lista del mejor valor global por iteración (para graficar convergencia)
    #  t → tiempo total de ejecución
    #  ev → cantidad total de evaluaciones
    #  pos1D → posiciones de las partículas en cada iteración
    x_best, val_best, hist, t, ev, pos1D = pso_1D()

    #   resultados del PSO 1D
    print(f"Mejor x = {x_best:.4f}, f(x) = {val_best:.4f}, tiempo = {t:.3f}s, evals = {ev}")

    # === GRAFICAR FUNCIÓN 1D Y PARTÍCULAS ===
    xs = np.linspace(-512, 512, 2000)   # crea 2000 puntos en el rango de búsqueda
    ys = f1(xs)                         # evaluar 
    
    plt.figure()
    plt.plot(xs, ys, 'k-', label='f1(x)')  # traza la función en negro (línea continua)

    # Grafica las posiciones de las partículas en cada iteración
    for it, pos in enumerate(pos1D[::1]):  # cada iteración (sin saltos)
        # Cada 'pos' es el conjunto de partículas en esa iteración
        plt.scatter(pos, f1(pos), s=15, alpha=0.6, label=f"Iter {it*10}" if it==0 else "")

    # Etiquetas y estética
    plt.title("PSO 1D: función y posiciones de partículas")
    plt.xlabel("x")
    plt.ylabel("f(x)")
    plt.legend()
    plt.grid(True)
    plt.show()



    # PSO en 2 dimensiones
    xy_best, val_best, hist2D, t2, ev2, pos2D = pso_2D()
    print(f"Mejor xy = {xy_best}, f(x,y) = {val_best:.4f}, tiempo = {t2:.3f}s, evals = {ev2}")

    # ===  GRAFICAR FUNCIÓN 2D Y PARTÍCULAS ===
    # Crea una cuadrícula de puntos (x,y)
    x = np.linspace(-100, 100, 200)
    y = np.linspace(-100, 100, 200)
    Xg, Yg = np.meshgrid(x, y)

    # Evalúa la función en toda la cuadrícula para graficar el mapa de contorno
    Z = np.array([[f2((xx, yy)) for xx, yy in zip(Xrow, Yrow)] for Xrow, Yrow in zip(Xg, Yg)])

    plt.figure()
    plt.contourf(Xg, Yg, Z, levels=50, cmap='viridis')  # mapa de calor con colores

    # Grafica las posiciones de las partículas cada 5 iteraciones
    for it, pos in enumerate(pos2D[::5]):
        plt.scatter(pos[:,0], pos[:,1], s=10, alpha=0.6, color='white')

    plt.title("PSO 2D: posiciones de partículas sobre f2(x,y)")
    plt.xlabel("x")
    plt.ylabel("y")
    plt.colorbar(label="f2(x,y)")  # escala de colores del valor de la función
    plt.show()


    # = GRAFICAR CONVERGENCIA (1D vs 2D) ===
    plt.plot(hist, label="PSO 1D")
    plt.plot(hist2D, label="PSO 2D")
    plt.xlabel("Iteración")
    plt.ylabel("Mejor valor f(x)")
    plt.legend()
    plt.title("Convergencia PSO")
    plt.grid(True)
    plt.show()
