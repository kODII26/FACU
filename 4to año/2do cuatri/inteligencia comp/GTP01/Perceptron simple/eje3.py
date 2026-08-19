from matplotlib.pyplot import plot
from grafica_perceptron import grafica_perceptron
from test_perceptron import test_perceptron
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
tol=0.00
max_epocas=100
tasa=0.001
print("APRENDIZAJE OR50--------------------")
training = "Perceptron simple/datasets/OR_50_trn.csv"
w,epocas,miss = grafica_perceptron(training,max_epocas,tol,tasa)
print("El error del aprendizaje fue de: ",miss*100,"%")
print("La cantidad de epocas para el aprendizaje fue de: ",epocas)

print("TESTEO OR50--------------------")
testing = "Perceptron simple/datasets/OR_50_tst.csv"
miss = test_perceptron(w,testing)
print("El error en el testeo fue de: ",miss*100,"%")

M = pd.read_csv(testing,header=None).to_numpy()
x1 = M[:,0]
x2 = M[:,1]
clases = M[:,2]
plt.scatter(x1[clases==1],x2[clases==1],color='blue',marker='o',label='Clase 1')
plt.scatter(x1[clases==-1],x2[clases==-1],color='red',marker='x',label='Clase -1')
plt.plot(x1,w[0]/w[1]-w[2]/w[1]*x1,color='green',linestyle='-',label='Linea divisoria')
plt.show()



print("APRENDIZAJE OR90--------------------")
training = "Perceptron simple/datasets/OR_90_trn.csv"
w,epoca,miss = grafica_perceptron(training,max_epocas,tol,tasa)
print("El error del aprendizaje fue de: ",miss*100,"%")
print("La cantidad de epocas para el aprendizaje fue de: ",epocas)


testing = "Perceptron simple/datasets/OR_90_tst.csv"
miss = test_perceptron(w,testing)
print("El error en el testeo fue de: ",miss*100,"%")


M = pd.read_csv(testing,header=None).to_numpy()
x1 = M[:,0]
x2 = M[:,1]
clases = M[:,2]
plt.scatter(x1[clases==1],x2[clases==1],color='blue',marker='o',label='Clase 1')
plt.scatter(x1[clases==-1],x2[clases==-1],color='red',marker='x',label='Clase -1')
plt.plot(x1,w[0]/w[1]-w[2]/w[1]*x1,color='green',linestyle='-',label='Linea divisoria')
plt.show()

print("\nConclusion: vemos que para los datos de OR90 es necesario tener un criterio de finalizacion adecuado ")
print("dado que colocar un criterio de 0% errores llevaria a que el metodo se ejecute infinitamente ")
print("debido a que la dispersion de los datos no permite que una recta divida al plano en dos zonas donde ")
print("de un lado caigan los resultados con yd==1 y del otro los resultados con yd==-1")

print("\nPor ello puede considerarse necesario para ese caso, si se requiere un error del 0% ")
print("un modelo que trabaje con mas entradas")