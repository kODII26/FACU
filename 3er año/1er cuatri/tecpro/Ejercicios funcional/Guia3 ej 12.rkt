#|12)Defina un procedimiento subst que reciba tres parámetros (dos valores y una lista)
y devuelva la lista con todos los componentes que son iguales al primer parámetro
reemplazados por el valor del segundo parámetro.
|#

(define (subst x y l)
  (if (null? l)
     l
    (if (eq? x (car l))
       (cons y (subst x y (cdr l)))
       (cons (car l) (subst x y (cdr l)))
       )
   )
  )
                             


(subst 'c 'k '( c o c o n u t)) 
