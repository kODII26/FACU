#|)Escriba una función que cuente la cantidad de apariciones de un elemento en una
lista. El primer parámetro será el elemento a buscar y el segundo la lista en la que
se debe buscar.
|#
(define (count-elem x l)
    (if (null? l)
         0
        (if (eq? x (car l))
            (+ 1 (count-elem x (cdr l)))
                  (count-elem x (cdr l))
       )
     )
 )

(count-elem 3 '(1 2 3 4 5 4 3 2 1 ))
(count-elem 7 '(7 7 7 7 7 7 7 ))
(count-elem 'a '(a b c d))




