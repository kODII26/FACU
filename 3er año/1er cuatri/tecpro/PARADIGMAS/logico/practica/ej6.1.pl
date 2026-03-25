% Declaraciones

estrella(sol).
planeta(mercurio).
planeta(venus).
planeta(tierra).
planeta(marte).
planeta(jupiter).
planeta(saturno).
planeta(urano).
planeta(neptuno).
planeta(pluton).
luna(luna).
luna(deimos).
luna(phobos).
luna(adrastea).
luna(aitne).
luna(amalthea).
luna(aoede).
luna(arche).
luna(autonoe).
luna(callisto).
luna(callirrhoe).
luna(aegir).
luna(albiorix).
luna(atlas).
luna(bebhionn).
luna(bergelmir).
luna(calypso).
luna(daphnis).
luna(ariel).
luna(belinda).
luna(bianca).
luna(despina).
luna(galatea).
luna(halimede).
luna(charon).
luna(nix).

orbita(luna, tierra).
orbita(deimos, marte).
orbita(phobos, marte).
orbita(callisto, jupiter).
orbita(adrastea, jupiter).
orbita(aitne, jupiter).
orbita(aegir, saturno).
orbita(albiorix, saturno).
orbita(atlas, saturno).
orbita(ariel, urano).
orbita(belinda, urano).
orbita(despina, neptuno).
orbita(galatea, neptuno).
orbita(charon, pluton).
orbita(nix, pluton).

% Reglas
lunaDe(Luna,Planeta) :- planeta(Planeta), luna(Luna), orbita(Luna,Planeta).