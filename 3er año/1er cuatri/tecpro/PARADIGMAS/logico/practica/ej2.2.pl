% Base de conocimiento
progenitor('Marcela','Justo').
progenitor('Julio','Justo').
progenitor('Coqui','Julio').
progenitor('Gloria','Julio').
progenitor('Julio','Franco').
progenitor('Julio','Martina').
hombre('Julio').
hombre('Coqui').
hombre('Franco').
mujer('Marcela').
mujer('Gloria').
mujer('Martina').


% Reglas
esPadre(Padre,Persona):-
    progenitor(Padre,Persona),
    hombre(Padre).

esMadre(Madre,Persona):-
    progenitor(Madre,Persona),
    mujer(Madre).

esAbuelo(Abuelo,Persona):-
    progenitor(Abuelo,Progenitor),
    progenitor(Progenitor,Persona),
    hombre(Abuelo).

esAbuela(Abuela,Persona):-
    progenitor(Abuela,Progenitor),
    progenitor(Progenitor,Persona),
    mujer(Abuela).

esHermano(Hermano,Persona):-
    progenitor(Progenitor,Persona),
    progenitor(Progenitor,Hermano),
    Persona \= Hermano,
    hombre(Hermano).

esHermana(Hermana,Persona):-
    progenitor(Progenitor,Persona),
    progenitor(Progenitor,Hermana),
    Persona \= Hermana,
    mujer(Hermana).


esSucesor(Sucesor,Persona):-progenitor(Persona,Sucesor).
esSucesor(Sucesor,Persona):-progenitor(Persona,X), esSucesor(Sucesor,X).
