factorial(0, 1):- !.

factorial(Numero, Factorial) :-
    Numero > 0,
    NumeroAnt is Numero - 1,
    factorial(NumeroAnt, FactorialAnt),
    Factorial is Numero * FactorialAnt.
