#|15)Defina en Racket un procedimiento recursivo que encuentre el primer elemento de
una lista que es un número. Debe retornar el número si lo encuentra, sino retornar
null.
Ej: (primer-num '((1 . 2) 'a (b) (5) 6 8 'a 9) → 6|#

(define (primer-num l) (if (null? l)
                           null
                           (if (number? (car l))
                               (car l)
                               (primer-num (cdr l))
                               )
                           )
  )

(primer-num '((1 . 2) 'a (b) (5) 6 8 'a 9))