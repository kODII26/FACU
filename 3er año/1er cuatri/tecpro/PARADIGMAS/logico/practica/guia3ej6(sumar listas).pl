sonIguales(A,B):-length(A,N),length(B,N).

suma_lista(Lista1,Lista2,ListaSuma):-
    sonIguales(Lista1,Lista2),
    suma_lista_aux(Lista1,Lista2,ListaSuma).


suma_lista_aux([],[],[]).

suma_lista_aux([Cabeza1|Resto1],[Cabeza2|Resto2],[CabezaSuma|ListaSuma]):-
    CabezaSuma is Cabeza1 + Cabeza2,
    suma_lista_aux(Resto1,Resto2,ListaSuma).
    

