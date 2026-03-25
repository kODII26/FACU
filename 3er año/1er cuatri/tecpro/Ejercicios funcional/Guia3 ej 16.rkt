#| 16 defina un procedimiento en Racket llamado attach-at-end que reciba como
parámetro un valor y una lista y retorne la lista con los mismos valores excepto el
que se pasó por parámetro que se agregará al final.
Ej: (attach-at-end 'prueba '(esto es una)) → (esto es una prueba |#
(define attach-at-end (lambda (x l)
                        (if (null? l)
                            (list x)
                            (cons (car l) (attach-at-end x (cdr l)))
                            )
                        )
  )
(attach-at-end 'prueba '(esto es una))
