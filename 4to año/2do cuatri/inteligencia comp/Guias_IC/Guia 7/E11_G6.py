import numpy as np
import matplotlib.pyplot as plt
import time

# Guia 6 - Ejercicio 1.1

# Definición de la función objetivo
def f(x):
    return -x * np.sin(np.sqrt(np.abs(x)))

# Derivada analítica de f(x)
def f_derivada(x):
    if x == 0:
        return 0
    return -np.sin(np.sqrt(np.abs(x))) - (x * np.cos(np.sqrt(np.abs(x)))) / (2 * np.sqrt(np.abs(x)))

# Decodificación binario a real
def decode(individuo, dominio, n_bits):
    valor_entero = 0
    for bit in individuo:
        valor_entero = (valor_entero << 1) | bit
    xmin, xmax = dominio
    real = xmin + (valor_entero / (2**n_bits - 1)) * (xmax - xmin)
    return real

# Algoritmo Genético 1D
def algoritmo_genetico(
    poblacion_size=30,
    generaciones=200,
    n_bits=16,
    dominio=(-512, 512),
    prob_cruza=0.8,
    prob_mutacion=0.01
):
    poblacion = np.random.randint(0, 2, (poblacion_size, n_bits))
    mejor_individuo = None
    mejor_valor = np.inf
    historia = []
    evals = 0
    no_mejora = 0
    max_no_mejora = 30  # criterio de parada
    t0 = time.time()

    for gen in range(generaciones):
        valores = np.array([f(decode(ind, dominio, n_bits)) for ind in poblacion])
        evals += poblacion_size

        idx_best = np.argmin(valores)
        if valores[idx_best] < mejor_valor:
            mejor_valor = valores[idx_best]
            mejor_individuo = poblacion[idx_best].copy()
            no_mejora = 0
        else:
            no_mejora += 1

        historia.append(mejor_valor)

        if no_mejora >= max_no_mejora:
            print(f"Parada anticipada en generación {gen+1} por falta de mejora.")
            break

        # Selección
        padres = []
        for _ in range(poblacion_size):
            i1, i2 = np.random.randint(0, poblacion_size, 2)
            padres.append(poblacion[i1] if valores[i1] < valores[i2] else poblacion[i2])
        padres = np.array(padres)

        # Cruza
        hijos = []
        for i in range(0, poblacion_size, 2):
            p1, p2 = padres[i], padres[i+1]
            if np.random.rand() < prob_cruza:
                punto = np.random.randint(1, n_bits-1)
                h1 = np.concatenate([p1[:punto], p2[punto:]])
                h2 = np.concatenate([p2[:punto], p1[punto:]])
            else:
                h1, h2 = p1.copy(), p2.copy()
            hijos.extend([h1, h2])
        hijos = np.array(hijos)

        # Mutación
        for ind in hijos:
            for j in range(n_bits):
                if np.random.rand() < prob_mutacion:
                    ind[j] = 1 - ind[j]

        poblacion = hijos

    tiempo = time.time() - t0
    mejor_x = decode(mejor_individuo, dominio, n_bits)
    return mejor_x, mejor_valor, historia, tiempo, evals

# Gradiente Descendente
def gradiente_descendente(
    lr=0.1,
    max_iter=1000,
    dominio=(-512, 512)
):
    x = np.random.uniform(dominio[0], dominio[1])
    mejor_x, mejor_valor = x, f(x)
    evals = 0
    t0 = time.time()

    for _ in range(max_iter):
        grad = f_derivada(x)
        x = x - lr * grad
        x = np.clip(x, dominio[0], dominio[1])
        valor = f(x)
        evals += 1
        if valor < mejor_valor:
            mejor_valor = valor
            mejor_x = x

    tiempo = time.time() - t0
    return mejor_x, mejor_valor, tiempo, evals

# Main
if __name__ == "__main__":
    mejor_x_ag, mejor_f_ag, hist_ag, t_ag, ev_ag = algoritmo_genetico()
    print(f"[AG] x = {mejor_x_ag:.5f}, f(x) = {mejor_f_ag:.5f}, tiempo = {t_ag:.3f}s, evals = {ev_ag}")

    mejor_x_gd, mejor_f_gd, t_gd, ev_gd = gradiente_descendente()
    print(f"[GD] x = {mejor_x_gd:.5f}, f(x) = {mejor_f_gd:.5f}, tiempo = {t_gd:.3f}s, evals = {ev_gd}")

    xs = np.linspace(-512, 512, 1000)
    ys = f(xs)
    plt.figure(figsize=(10,5))
    plt.plot(xs, ys, label="f(x)")
    plt.scatter(mejor_x_ag, mejor_f_ag, color="red", label="Mínimo AG")
    plt.scatter(mejor_x_gd, mejor_f_gd, color="green", label="Mínimo GD")
    plt.title("Optimización (AG vs GD)")
    plt.xlabel("x"); plt.ylabel("f(x)")
    plt.legend(); plt.grid(True)
    plt.show()
