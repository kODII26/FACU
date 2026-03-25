ruta(santafe, parana).
ruta(parana, corrientes).
ruta(santafe, cordoba).
ruta(santafe, coronda).
ruta(santafe, rosario).
ruta(rosario, capital).
ruta(rosario, mardelplata).
ruta(capital, cordoba).

desdehasta(A,B):- ruta(A,B).
desdehasta(A,B):- ruta(A,X),desdehasta(X,B).
