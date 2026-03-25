mujer(haydee).
mujer(tania).
hombre(livio).
hombre(pedro).
profesion(haydee,abogado).
profesion(haydee,ingeniero).
profesion(tania,medico).
profesion(livio,contador).
profesion(pedro,abogado).
libro('Rayuela',novela,largo).
libro('Karamazov',novela,largo).
libro('Octaedro',cuento,corto).
libro('Inventario',poema,largo).
libro('Leones',novela,corto).



gusta(Persona,Libro):-profesion(Persona,abogado),libro(Libro,novela,largo).

gusta(Persona,Libro):-profesion(Persona,ingeniero),libro(Libro,novela,_).
gusta(Persona,Libro):-profesion(Persona,medico),libro(Libro,novela,_).

gusta(Persona,Libro):-mujer(Persona),libro(Libro,_,largo).

gusta(Persona,Libro):-profesion(Persona,contador),hombre(Persona),libro(Libro,cuento,_);libro(Libro,poema,_).


