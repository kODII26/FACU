ins(X, L, [X | L]).
ins(X, [Y | L1], [Y | L2]) :- ins(X, L1, L2).
per([], []).
per([X | L], Lp) :- per(L, L1), ins(X, L1, Lp).
