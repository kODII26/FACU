% Caso base: Si la lista está vacía, la lista plana también está vacía.
aplanar([], []).

% Caso recursivo: Si el primer elemento es una lista, aplana ese elemento y continúa con el resto.
aplanar([Cabeza|Resto], ListaPlana):- 
    is_list(Cabeza), 
    aplanar(Cabeza, ListaPlanaCabeza), 
    aplanar(Resto, ListaPlanaResto), 
    append(ListaPlanaCabeza, ListaPlanaResto, ListaPlana).

% Caso recursivo: Si el primer elemento no es una lista, agrégalo directamente a la lista plana.
aplanar([Cabeza|Resto], [Cabeza|ListaPlanaResto]):- 
    \+ is_list(Cabeza), 
    aplanar(Resto, ListaPlanaResto).