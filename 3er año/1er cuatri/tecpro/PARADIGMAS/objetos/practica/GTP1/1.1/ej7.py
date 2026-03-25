costo_dia_alquiler = float(input("Introduce el costo por día de alquiler del vehículo: "))
numero_dias = int(input("Introduce el número de días de alquiler: "))
presupuesto_combustible = float(input("Introduce el presupuesto para combustible: "))
# Calcula el costo total del viaje
total= (costo_dia_alquiler*numero_dias)+presupuesto_combustible

# Imprime el costo total
print(total)
