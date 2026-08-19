import numpy as np
import pandas as pd
def learn_perceptron(training,tol,max_epocas,tasa):
    M = pd.read_csv(training, header=None).to_numpy()
    cant_entradas = M.shape[1]-1
    cant_patrones = M.shape[0]

    w = (np.random.rand(cant_entradas + 1)*2 - 1)*0.5
    f_sign = lambda y: -1*(y<0) + 1*(y>=0)
    yd = M[: , cant_entradas]

    miss = tol+1
    epoca = 0

    while epoca<max_epocas and miss>tol:
        for i in range(cant_patrones):
            entradas = np.insert(M[i,:-1],0,-1)
            y_obtenida = f_sign(np.dot(w,entradas))
            w = w + tasa/2*(yd[i] - y_obtenida)*entradas

        y_obtenida = np.zeros(cant_patrones)
        for i in range(cant_patrones):
            entradas = np.insert(M[i,:-1],0,-1)
            y_obtenida[i] = f_sign(np.dot(w,entradas))
        
        miss = np.sum(np.abs(y_obtenida - yd)>0)/cant_patrones
        epoca = epoca + 1
    return w,miss,epoca