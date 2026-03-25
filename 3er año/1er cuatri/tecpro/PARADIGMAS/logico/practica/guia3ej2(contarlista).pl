
contar(_,[],0).

contar(Elemento, [Elemento|Resto], Cantidad):- 
    contar(Elemento, Resto, CantidadResto), 
    Cantidad is CantidadResto + 1.

contar(Elemento, [Otro|Resto], Cantidad):- 
    Elemento \= Otro, 
    contar(Elemento, Resto, Cantidad).