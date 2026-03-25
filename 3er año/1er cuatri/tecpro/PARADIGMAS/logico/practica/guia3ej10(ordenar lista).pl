insertar(Num,[],[Num]).

insertar(Num,[Cabeza|Resto],[Cabeza|Resultado]):-
    Num>Cabeza,
    insertar(Num,Resto,Resultado).

insertar(Num, [Cabeza|Resto], [Num, Cabeza|Resto]):- 
    Num =< Cabeza.

ordenar([],[]).

ordenar([Cabeza|Resto],ListaOrdenada):-
    ordenar(Resto,ListaOrdenadaResto),
    insertar(Cabeza,ListaOrdenadaResto,ListaOrdenada ).

