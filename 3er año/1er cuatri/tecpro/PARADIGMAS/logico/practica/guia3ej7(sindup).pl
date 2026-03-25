eliminar_dup([],[]).

eliminar_dup([Cabeza|Resto],[Cabeza|SinDup]):-
    \+ member(Cabeza,Resto),
    eliminar_dup(Resto,SinDup).


eliminar_dup([Cabeza|Resto],SinDup):-
    member(Cabeza,Resto),
    eliminar_dup(Resto,SinDup).

