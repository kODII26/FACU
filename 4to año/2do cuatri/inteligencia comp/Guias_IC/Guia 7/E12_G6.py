import numpy as np
import matplotlib.pyplot as plt
import time

# Guia 6 - Ejercicio 1.2

def f2(x, y):
    r2 = x**2 + y**2
    return (r2**0.25) * (np.sin(50 * (r2**0.1))**2 + 1)

def gradiente_numerico(xy, h=1e-5):
    x, y = xy
    grad_x = (f2(x + h, y) - f2(x - h, y)) / (2*h)
    grad_y = (f2(x, y + h) - f2(x, y - h)) / (2*h)
    return np.array([grad_x, grad_y])

def decode(individuo, dominio, n_bits):
    bits_x = individuo[:n_bits]
    bits_y = individuo[n_bits:]
    def binario_a_real(bits):
        valor_entero = 0
        for bit in bits:
            valor_entero = (valor_entero << 1) | bit
        xmin, xmax = dominio
        return xmin + (valor_entero / (2**n_bits - 1)) * (xmax - xmin)
    x = binario_a_real(bits_x)
    y = binario_a_real(bits_y)
    return x, y

# Algoritmo Genético 2D
def algoritmo_genetico_2D(
    poblacion_size=30,
    generaciones=300,
    n_bits=12,
    dominio=(-100, 100),
    prob_cruza=0.8,
    prob_mutacion=0.01
):
    long_cromosoma = 2 * n_bits
    poblacion = np.random.randint(0, 2, (poblacion_size, long_cromosoma))
    mejor_individuo = None
    mejor_valor = np.inf
    historia = []
    evals = 0
    no_mejora = 0
    max_no_mejora = 30
    t0 = time.time()

    for gen in range(generaciones):
        valores = []
        for ind in poblacion:
            x, y = decode(ind, dominio, n_bits)
            valores.append(f2(x, y))
        valores = np.array(valores)
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

        padres = []
        for _ in range(poblacion_size):
            i1, i2 = np.random.randint(0, poblacion_size, 2)
            padres.append(poblacion[i1] if valores[i1] < valores[i2] else poblacion[i2])
        padres = np.array(padres)

        hijos = []
        for i in range(0, poblacion_size, 2):
            p1, p2 = padres[i], padres[i+1]
            if np.random.rand() < prob_cruza:
                punto = np.random.randint(1, long_cromosoma-1)
                h1 = np.concatenate([p1[:punto], p2[punto:]])
                h2 = np.concatenate([p2[:punto], p1[punto:]])
            else:
                h1, h2 = p1.copy(), p2.copy()
            hijos.extend([h1, h2])
        hijos = np.array(hijos)

        for ind in hijos:
            for j in range(long_cromosoma):
                if np.random.rand() < prob_mutacion:
                    ind[j] = 1 - ind[j]

        poblacion = hijos

    tiempo = time.time() - t0
    mejor_x, mejor_y = decode(mejor_individuo, dominio, n_bits)
    return (mejor_x, mejor_y), mejor_valor, historia, tiempo, evals

def gradiente_descendente_2D(
    lr=0.05,
    max_iter=2000,
    dominio=(-100, 100)
):
    xy = np.random.uniform(dominio[0], dominio[1], 2)
    mejor_xy, mejor_valor = xy.copy(), f2(*xy)
    evals = 0
    t0 = time.time()

    for _ in range(max_iter):
        grad = gradiente_numerico(xy)
        xy = xy - lr * grad
        xy = np.clip(xy, dominio[0], dominio[1])
        valor = f2(*xy)
        evals += 4
        if valor < mejor_valor:
            mejor_valor = valor
            mejor_xy = xy.copy()

    tiempo = time.time() - t0
    return mejor_xy, mejor_valor, tiempo, evals

# Main
if __name__ == "__main__":
    mejor_xy_ag, mejor_f_ag, hist_ag, t_ag, ev_ag = algoritmo_genetico_2D()
    print(f"[AG] (x, y) = {mejor_xy_ag}, f(x,y) = {mejor_f_ag:.5f}, tiempo = {t_ag:.3f}s, evals = {ev_ag}")

    mejor_xy_gd, mejor_f_gd, t_gd, ev_gd = gradiente_descendente_2D()
    print(f"[GD] (x, y) = {mejor_xy_gd}, f(x,y) = {mejor_f_gd:.5f}, tiempo = {t_gd:.3f}s, evals = {ev_gd}")

    X = np.linspace(-100, 100, 300)
    Y = np.linspace(-100, 100, 300)
    XX, YY = np.meshgrid(X, Y)
    Z = (XX**2 + YY**2)**0.25 * (np.sin(50*(XX**2+YY**2)**0.1)**2 + 1)
    plt.figure(figsize=(10,6))
    plt.contourf(XX, YY, Z, levels=100, cmap="jet")
    plt.colorbar(label="f(x,y)")
    plt.scatter(mejor_xy_ag[0], mejor_xy_ag[1], color="red", label="Mínimo AG")
    plt.scatter(mejor_xy_gd[0], mejor_xy_gd[1], color="green", label="Mínimo GD")
    plt.title("Optimización (AG vs GD) 2D")
    plt.xlabel("x"); plt.ylabel("y")
    plt.legend(); plt.show()
