padrede(leoncio, alberto).
padrede(leoncio, geronimo).

padrede(alberto, juan).
padrede(alberto, luis).

padrede(geronimo, luisa).

eshermano(A,B):-padrede(P,A),padrede(P,B), A \= B.
esnieto(A,B):-padrede(P,A),padrede(B,P).

