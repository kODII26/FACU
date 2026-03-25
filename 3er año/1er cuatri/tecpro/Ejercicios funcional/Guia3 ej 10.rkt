;Escriba una función largo que devuelva el largo de una lista sin utilizar la función
;definida en Racket.
#lang racket


(define (largo l)(if (null? l)
                     0
                     (+ 1 (largo (cdr l)))
                     )
  )

(largo '(1 4 8))
(largo '(1 4 8 9))
