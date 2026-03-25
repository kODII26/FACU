#|Defina una función distance2d que reciba como parámetros dos puntos en el plano
y devuelva su distancia. Utilice una lista impropia para la declaración de x e y
|#
#lang racket
(define (dist2d p1 p2)
  (let ((x (- (car p2) (car p1)))
         (y (- (cdr p2) (cdr p1))))
         (sqrt (+ (* x x) (* y y)))))

(dist2d '(1 . 1) '(2 . 2))
