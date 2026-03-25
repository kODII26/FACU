#| 13)Se desea crear un función que reciba como parámetros una lista de átomos
compuesto únicamente de letras y devuelva una lista agrupando los que son iguales
en sublistas. |#
(define (wrapper x l) 
(if (null? l)
                         l
                         (if (eq? x (car l))
                             (cons (car l) (wrapper x (cdr l)))
                             (wrapper x (cdr l)))))
(define (elimina x l) 
(if (null? l)
                          l
                          (if (eq? x (car l))
                              (elimina x (cdr l))
                              (cons (car l) (elimina x (cdr l))))))

(define (agrupar l) 
(if (null? l)
                        l
                        (cons (wrapper (car l) l) (agrupar (elimina (car l) (cdr l))))
                        )
  )
                        


(agrupar '(A A B C A B A D C))
; --> ((AAAA) (BB) (CC) (D))