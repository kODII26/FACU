import numpy as np
import pandas as pd
def test_perceptron(w,testing):
    M = pd.read_csv(testing,header=None).to_numpy()
    cant_entradas = M.shape[1]-1
    cant_patrones = M.shape[0]

    f_sign = lambda y: -1*(y<0) + 1*(y>=0)
    yd = M[: , cant_entradas]
    y_obtenida = np.zeros(cant_patrones)

    for i in range(cant_patrones):
        entradas = np.insert(M[i,:-1],0,-1)
        y_obtenida[i] = f_sign(np.dot(w,entradas))

    miss = np.sum(np.abs(y_obtenida-yd)>0)/cant_patrones
    return miss