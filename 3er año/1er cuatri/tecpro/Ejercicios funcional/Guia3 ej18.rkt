(define-struct punto (x y))

(define dist2d (lambda (p1 p2) (let* ((x0 (- (punto-x p1) (punto-x p2)))
                                     (y0 (- (punto-y p1) (punto-y p2)))
                                     )
                                 (sqrt (+ (* x0 x0) (* y0 y0)))
                                 )))
(define p1 (make-punto 2 4))
(define p2 (make-punto 1 1))

(dist2d p1 p2)