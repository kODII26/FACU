% Cuerpo de conocimiento
entrada('Bombones de jamon').
entrada('Empanada').
entrada('Tarta de Atun').

principal('Locro').
principal('Asado').
principal('Atados de repollo').

postre('Dulce de batata').
postre('Alfajor norteño').  
postre('Flan').

carta(X,Y,Z) :- entrada(X), principal(Y), postre(Z).













