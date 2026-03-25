#| así se comenta (que locura soy)
|#

#lang racket
(define (mascorta l1 l2)
  (if (< (length l2) (length l1))
    l2
    l1
   )
  )

(mascorta '(a b) '(c d e))
(mascorta '(a b) '(c d))
(mascorta '(a b) '(c))

  
