
cantidad([],0).

cantidad([_|Resto],Elementos):-
    cantidad(Resto,ElementosResto),
    Elementos is ElementosResto+1.

