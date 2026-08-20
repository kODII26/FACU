import numpy as np
from sklearn.neural_network import MLPClassifier
from sklearn.model_selection import cross_val_score
import pandas as pd
import matplotlib.pyplot as plt

def algoritmo_genetico_mlp(X_train, y_train,
                           poblacion_size=30,
                           generaciones=50,
                           prob_cruza=0.8,
                           prob_mutacion=0.01,
                           hidden_layer_sizes=(50,),  # capas del MLP
                           random_state=42):
   
    mejores_por_gen = []
    promedios_por_gen = []
    np.random.seed(random_state)
    n_genes = X_train.shape[1]
    poblacion = np.random.randint(0, 2, (poblacion_size, n_genes))
    
    mejor_individuo = None
    mejor_fitness = -np.inf  # queremos maximizar la precisión por eso un -inf, cualq valor es mayor a este
    
    for gen in range(generaciones):
        fitness = []
        
        # Evaluamos cada individuo
        for ind in poblacion:

            seleccion = np.where(ind == 1)[0]
            #Guardamos el indice de columnas al azar que vamos a usar
            if len(seleccion) == 0:
                fitness.append(0)
                continue    # el continue lo que hace es ir a la siguiente poblacion
            
            
            X_sub = X_train[:, seleccion]   #Agarro las columnas seleccionadas y todas las filas 
            mlp = MLPClassifier(hidden_layer_sizes=hidden_layer_sizes, max_iter=500, random_state=random_state)
            score = cross_val_score(mlp, X_sub, y_train, cv=5).mean()
            #Usamos la validacion cruzada usando 5 folds
            fitness.append(score)
        
        fitness = np.array(fitness)
        
        # Mejor individuo
        idx_best = np.argmax(fitness)
        if fitness[idx_best] > mejor_fitness:
            mejor_fitness = fitness[idx_best]
            mejor_individuo = poblacion[idx_best].copy()
        
        # Selección por torneo
        padres = []
        for _ in range(poblacion_size):
            i1, i2 = np.random.randint(0, poblacion_size, 2)
            if fitness[i1] > fitness[i2]:
                padres.append(poblacion[i1])
            else:
                padres.append(poblacion[i2])
        padres = np.array(padres)
        
        # Cruza de un punto
        hijos = []
        for i in range(0, poblacion_size, 2):
            p1, p2 = padres[i], padres[i+1]
            if np.random.rand() < prob_cruza:
                punto = np.random.randint(1, n_genes-1)
                h1 = np.concatenate([p1[:punto], p2[punto:]])
                h2 = np.concatenate([p2[:punto], p1[punto:]])
            else:
                h1, h2 = p1.copy(), p2.copy()
            hijos.extend([h1, h2])
        hijos = np.array(hijos)
        
        # Mutación
        for ind in hijos:
            for j in range(n_genes):
                if np.random.rand() < prob_mutacion:
                    ind[j] = 1 - ind[j]
        
        poblacion = hijos
        mejores_por_gen.append(fitness.max())
        promedios_por_gen.append(fitness.mean())
    
    plt.plot(mejores_por_gen, label="Mejor fitness")
    plt.plot(promedios_por_gen, label="Fitness promedio")
    plt.xlabel("Generación")
    plt.ylabel("Fitness (precisión)")
    plt.legend()
    plt.title("Evolución del algoritmo genético")
    plt.show()
    return mejor_individuo, mejor_fitness


##Leemos los datos

# Leer archivo de entrenamiento
train_df = pd.read_csv("leukemia_train.csv")
# Leer archivo de prueba
test_df = pd.read_csv("leukemia_test.csv")
# Entrenamiento
X_train = train_df.iloc[:, :-1].values  # todas las columnas menos la última
y_train = train_df.iloc[:, -1].values   # última columna = etiqueta
# Prueba
X_test = test_df.iloc[:, :-1].values
y_test = test_df.iloc[:, -1].values


mejor_genes, mejor_score = algoritmo_genetico_mlp(X_train, y_train, poblacion_size=20,
                                                  generaciones=20, 
                                                  hidden_layer_sizes=(10,))

print("Mejor precisión MLP:", mejor_score)
print("Cantidad de genes seleccionados:", mejor_genes.sum())

X_train=X_train[:, np.where(mejor_genes == 1)[0]]

X_test=X_test[:, np.where(mejor_genes == 1)[0]]

mlp_final = MLPClassifier(hidden_layer_sizes=(10,), max_iter=500, random_state=42)
mlp_final.fit(X_train, y_train)
test_score = mlp_final.score(X_test, y_test)
print("Precisión en test con genes seleccionados:", test_score)

