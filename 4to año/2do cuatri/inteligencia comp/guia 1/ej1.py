import csv

with open('datos.csv', mode='r', encoding='utf-8') as archivo:
    lector = csv.reader(archivo)
    for fila in lector:
        print(fila)  # Cada fila es una lista de texto

