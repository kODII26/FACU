#lang racket
(cdddr'( a b c . x))

(car(cdddr '(a b c x)))

(cdr(car'((a . x) b)))

(car'(x . a))

(cdr '(a . x))




