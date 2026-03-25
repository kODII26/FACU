eliminar_primero([],_,[]).

eliminar_primero([Cabeza|Resto],Num,Resto):-
    Cabeza=Num,
    !.

eliminar_primero([Cabeza|Resto],Num,[Cabeza|X]):-
    eliminar_primero(Resto,Num,X).

