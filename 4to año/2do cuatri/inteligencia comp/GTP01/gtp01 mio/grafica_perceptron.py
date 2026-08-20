import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
from matplotlib.animation import FuncAnimation

def grafica_perceptron(training, max_epocas, tol, tasa):
    M = pd.read_csv(training, header=None).to_numpy()
    cant_entradas = M.shape[1]-1
    cant_patrones = M.shape[0]

    w = (np.random.rand(cant_entradas+1)*2-1)*0.5
    yd = M[:,cant_entradas]
    f_sign = lambda y: 1*(y>=0) -1*(y<0)


    fig, ax = plt.subplots()    #devuelve una tupla, figura y ejes

    #graficamos la linea
    x = np.linspace(-2, 2, 100) 
    y = w[0]/w[2]- w[1]/w[2]*x
    line, = ax.plot(x, y)       #plot devuelve una lista de lineas, en este caso dibujamos solo una
                                #por lo que obtenemos el primer elemento (y unico) de la lista en la variable line
    
    #primero vamos a visualizar los patrones
    clases = M[:,cant_entradas]
    ax.scatter(M[clases==1,0] , M[clases==1,1], color='blue', label='Clase 1')
    ax.scatter(M[clases==-1,0] , M[clases==-1,1], color='red', label='Clase -1')
    

    
    #Funcion para inicializar el grafico
    #Si no se la agrego me hace una primera pasada por la funcion
    #donde calculo los pesos y me arruina el contador de epocas
    def init():
        return line,
        
    epoca = 0
    miss = 1.0

    def muestra_aprendizaje(frame):
        nonlocal w, epoca, miss  #para que me utilice las variables que declare antes

        y_obtenida = np.zeros(cant_patrones)
        for i in range(cant_patrones):
            entradas = np.insert(M[i,:-1],0,-1)
            y_obtenida[i] = f_sign(np.dot(w,entradas))
            w = w + tasa/2*(yd[i] - y_obtenida[i])*entradas

        epoca = frame + 1
        errores = np.sum(yd != y_obtenida)
        miss = errores/cant_patrones
        y = w[0]/w[2]- w[1]/w[2]*x
        line.set_ydata(y) # mueve la recta que ya existe
        if tol>=miss or frame == max_epocas - 1:
            ani.event_source.stop() #detiene la animacion
        return line,

    ani = FuncAnimation(fig, muestra_aprendizaje, init_func=init, frames=max_epocas, interval=100, blit=False, repeat=False)
    
    #para guardar la animacion, ani.save() se debe llamar solo o antes de plot.show()
    #ani.save('animacion.gif', writer='pillow')
    
    plt.show() 
    return w,epoca,miss