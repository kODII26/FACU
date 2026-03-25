

positivos([],[]).

positivos([Cabeza|Resto],[Cabeza|ListaPositivos]):- % Agg cabeza a listapositivos
    Cabeza>=0,
    positivos(Resto,ListaPositivos).
    
positivos([Cabeza|Resto], ListaPositivos):- 
    Cabeza < 0, 
    positivos(Resto, ListaPositivos).


    