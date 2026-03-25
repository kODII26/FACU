#### CONSIGNA


Implementar una función `void stack2queue(stack<int> &S, queue<int> &Q, bool (*pred)(int));`
que replique los elementos de una pila `S` en una cola `Q`, ordenando sus elementos según un predicado `bool pred(int n)`, quedando:

- Los elementos que cumplen con `pred`, en las primeras posiciones de `Q` desde el frente, en el orden de profundidad en la pila (el más alto en la pila queda más adelante en la cola),
- El resto de los elementos en las posiciones siguientes, en orden invertido respecto a su profundidad en la pila.

Es decir debe quedar: `Q = ([elementos que cumplen con el predicado],[elementos que no])`, ordenados en cada grupo de acuerdo a su distancia respecto del tope de la pila, los que no cumplen pred, en orden inverso). 

#### EJEMPLOS

**Notación:** pila `S = {fondo, ...,tope}`, cola `Q = {frente, ..., fondo}`

```
S = {1,2}, pred: es_par(), => Q = {2,1}
S = {1,2}, pred: es_impar(), => Q = {1,2}

S = {3,1,5,4}, pred: es_par(), => Q = {4,3,1,5}
S = {3,1,5,4}, pred: es_impar(), => Q = {5,1,3,4}

S = {1,4,3,6,5,2}, pred: es_par(), => Q={2,6,4,1,3,5}, 
S = {1,4,3,6,5,2}, pred: es_impar() =>Q={5,3,1,4,6,2}
```

#### ENLACE AL ZIP

[ENLACE](https://drive.google.com/file/d/1EhvOAIu24ruB-UnU2xvtjziv2C-Z07ui/view?usp=drive_link)
