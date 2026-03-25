
% localidad(Nro, Nombre, CostoHastaSiguiente)
localidad(1, 'Cordoba Capital', 1500).
localidad(2, 'Carlos Paz', 1500).
localidad(3, 'Bialet Masse', 1000).
localidad(4, 'Valle Hermoso', 1200).
localidad(5, 'La Falda', 1000).
localidad(6, 'Huerta Grande', 1200).
localidad(7, 'La Cumbre', 1600).
localidad(8, 'Capilla del Monte', 0).

% persona(Nombre, LocalidadInicio, LocalidadFin)
persona(jorge, 'Cordoba Capital', 'La Falda').
persona(adriana, 'Valle Hermoso', 'La Cumbre').
persona(gabriela, 'Carlos Paz', 'Capilla del Monte').
persona(roberto, 'Bialet Masse', 'Huerta Grande').
persona(jose, 'Cordoba Capital', 'Capilla del Monte').

% camino_persona(Persona, Camino) 
camino_persona(Persona, Camino) :-
    persona(Persona, Inicio, Fin), % Obtiene su localidad de inicio y fin
    camino(Inicio, Fin, Camino), !. % Construye lista de localidades "Camino" que tiene que recorrer

% camino(Inicio, Fin, Camino)
camino(Inicio, Fin, Camino) :-
    localidad(N1, Inicio, _),
    localidad(N2, Fin, _),
    N1 =< N2, % Se asegura que se viaje para adelante
    camino_aux(N1, N2, Camino).

% camino_aux(N1, N2, Camino) %VER MEJOR
camino_aux(N, N, [Loc]) :-
    localidad(N, Loc, _), !.
camino_aux(N1, N2, [Loc|Resto]) :-
    localidad(N1, Loc, _),
    N1 < N2,
    Nsig is N1 + 1,
    camino_aux(Nsig, N2, Resto).


% tramos_camino([A,B,C], [[A,B],[B,C]])
tramos_camino([_], []) :- !.
tramos_camino([A,B|Resto], [[A,B]|Tramos]) :- % Convierte lista de localidades en lista de tramos
    tramos_camino([B|Resto], Tramos).

% Unir dos listas (sin append)
unir([], L, L) :- !.
unir([X|R], L, [X|R2]) :- unir(R, L, R2).


% tramos_personas(ListaPersonas, ListaTramos)
tramos_personas([], []) :- !.
tramos_personas([P|Resto], TramosTotal) :-
    camino_persona(P, Camino),
    tramos_camino(Camino, TramosP), %VER MEJOR esta linea
    tramos_personas(Resto, TramosResto),
    unir(TramosP, TramosResto, TramosTotal).


% contar_usuarios_tramo(Tramo, ListaPersonas, Cantidad) %VER MEJOR
contar_usuarios_tramo(_, [], 0) :- !.
contar_usuarios_tramo([A,B], [P|Resto], Cant) :-
    camino_persona(P, Camino),
    pertenece_tramo([A,B], Camino), !, % SI tramo pertenece a la lista camino corta y no busca otro tramo en esa lista
    contar_usuarios_tramo([A,B], Resto, CantR), 
    Cant is CantR + 1.
contar_usuarios_tramo([A,B], [_|Resto], Cant) :-
    contar_usuarios_tramo([A,B], Resto, Cant).
    

% pertenece_tramo([A,B], Camino)
pertenece_tramo([A,B], [A,B|_]) :- !.
pertenece_tramo([A,B], [_|R]) :- pertenece_tramo([A,B], R).


% costo_tramo([A,B], Costo) %VER MEJOR
costo_tramo([A,B], Costo) :-
    localidad(N1, A, Costo),
    localidad(N2, B, _),
    N2 is N1 + 1, !.

% costo_total_persona(Persona, ListaPersonas, CostoTotal)
costo_total_persona(Persona, ListaPersonas, CostoTotal) :-
    camino_persona(Persona, Camino), % Obtiene todos los caminos de 1 persona
    tramos_camino(Camino, Tramos), % Divide todos los caminos en lista de tramos
    costo_tramos_persona(Tramos, ListaPersonas, 0, CostoTotal).

% costo_tramos_persona(Tramos, ListaPersonas, Acum, Total)
costo_tramos_persona([], _, Acum, Acum) :- !.
costo_tramos_persona([Tramo|Resto], ListaPersonas, Acum, Total) :-
    costo_tramo(Tramo, CostoTramo), % Encuentra el costo de ese tramo en particular
    contar_usuarios_tramo(Tramo, ListaPersonas, Cant), % Cuenta cuantos recorren ese tramo
    CostoParcial is CostoTramo // Cant, % Divide el precio entre esas personas 
    Acum1 is Acum + CostoParcial, 
    costo_tramos_persona(Resto, ListaPersonas, Acum1, Total). % Sigue recursivamente


% Nuevo predicado principal
repartir_costos(Personas, Resultado) :-
    repartir_costos_aux(Personas, Personas, Resultado).

% Auxiliar que mantiene la lista completa
repartir_costos_aux([], _, []) :- !.
repartir_costos_aux([P|Resto], Todos, [[P, Camino, CostoTotal]|Resultado]) :- % Guarda el camino y costototal de cada persona en la lista Resultado
    camino_persona(P, Camino), % Encuentra el camino q recorre esa persona
    costo_total_persona(P, Todos, CostoTotal), % Halla el costo total
    repartir_costos_aux(Resto, Todos, Resultado).


