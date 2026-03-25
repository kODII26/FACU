
#### CONSIGNA

Escribir una función `int cubrimientos(list<set<int>> L);` que dada una lista de conjuntos de enteros `L`, devuelva el número de selecciones posibles de conjuntos en `L` tal que todos los elementos estén en dicha selección. 

#### Ejemplos:

```
L = {{1,2},{2,3},{3}} => 3 // i.e. {{1,2},{2,3}},{{1,2},{3}},{{1,2}.{2,3},{3}}
L = {} => 1 // i.e. {}
L = {{1}} => 1 // i.e. {1}
L = {{1},{2},{3}} => 1 // i.e.{{1},{2},{3}}
L = {{1},{2},{1,2,3}} => 4 // {{1},{1,2,3}},{{2},{1,2,3}},{{1},{2}{1,2,3}},{1,2,3}}
```

#### AYUDA

- Obtener `U`, el conjunto universal para los conjuntos de `L`.
- Obtener `P`, el conjunto potencia de `L` (todas las combinaciones posibles de conjuntos en `L`).
- Para cada `p` de `P`,  hacer la unión de los conjuntos en cada `p` y determinar si es cubrimiento de `U`. De serlo, incrementar en uno el contador.

#### ENLACE AL ZIP

[ENLACE](https://drive.google.com/file/d/1DDte7haIghufnBD0nDSPpUHQ3VX_Uf5x/view?usp=drive_link)
