from grafica_perceptron import grafica_perceptron
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
tol=0.00
max_epocas=100
tasa=0.001
training = "Perceptron simple/datasets/OR_trn.csv"
w,epoca,miss = grafica_perceptron(training,max_epocas,tol,tasa)

training = "Perceptron simple/datasets/XOR_trn.csv"
w,epoca,miss = grafica_perceptron(training,max_epocas,tol,tasa)