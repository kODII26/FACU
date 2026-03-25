suma([],0).

suma([Cabeza|Resto],X):-
    suma(Resto,Xresto),
    X is Cabeza + Xresto.



