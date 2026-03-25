; AGREGRA UN ELEMENTO AL FINAL DE UNA LISTA

(define attach-at-end
  (lambda (valor lista)
    (cond
      ;; Si la lista está vacía, devolvemos una lista con el valor como único elemento
      ((null? lista) (list valor))
      ;; En otro caso, llamamos recursivamente a attach-at-end con el cdr de la lista
      (else (cons (car lista) (attach-at-end valor (cdr lista)))))))

(display (attach-at-end 'prueba '(esto es una)))


;SUMAR ELEMENTOS DE UNA LISTA
apply


;DAR VUELTA UNA LISTA

(define (fullreverse lista)
  (if (null? lista)
      '()
      (append (fullreverse (cdr lista)) (list(car lista)))
  ))


;; Ordenar la lista utilizando la función sort
(define lista-ordenada (sort lista-desordenada <))

; ENCONTRAR UN ELEMENTO (NUMERO EN ESTE CASO) EN UNA LISTA

(define (primer-num lista)
  (cond
    ;; Si la lista está vacía, devuelve 'null
    ((null? lista) 'null)
    
    ;; Si el primer elemento es un número, devuelve ese número
    ((number? (car lista)) (car lista))
    
    ;; Si el primer elemento no es un número, continúa buscando en el resto de la lista
    (else (primer-num (cdr lista)))))

(display (primer-num '((1 . 2) 'a (b) (5) 6 8 'a 9)))

; REEMPLAZAR ELEMENTOS DE UNA LISTA POR OTROS

(define reemplazar-elemento (lambda (viejo nuevo lista)
  (if (null? lista)
      lista ; Devolvemos una lista vacía si la lista original está vacía
      (if (eq? (car lista) viejo)
          (cons nuevo (reemplazar-elemento viejo nuevo (cdr lista))) ; Reemplazamos el elemento viejo por el nuevo
          (cons (car lista) (reemplazar-elemento viejo nuevo (cdr lista)))))))

(display (reemplazar-elemento 'c 'k '(c o c o n u t)))


;FUNCION AUXILIAR PARA CONTAR LA CANTIDAD DE ELEMENTOS DISTINOS DENTRO DE LA LISTA 
(define contar
  (lambda (x lista)
    (if (null? lista)
        0
        (if (eq? (car lista) x)
            (+ (contar x (cdr lista)) 1)
            (contar x (cdr lista))
            )
        )
    )
  )

;FUNCION AUXILIAR PARA ELIMINAR ELMENTOS DE UNA LISTA
(define eliminar
  (lambda (x lista)
    (if (null? lista)
        lista
        (if (eq? x (car lista))
            (eliminar x (cdr lista)) ; se ignora el elemento a eliminar y se contruye la lista sin ese elemento
            (cons (car lista) (eliminar x (cdr lista)))
            )
        )
    )
  )

;EJEMPLO BASICO DEL USO DE MAP
(define lista '(1 2 3 4 5))

(define (incrementar n)
  (+ n 1))

(map incrementar lista)  ; Devuelve: (2 3 4 5 6)

;///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#t → verdadero
#f → falso
#(esto es un vector de símbolos)
#\a es un caracter

> (quote (3 1 4 pi)); quote no evalua pi ya que no toma a los comp de la lista como variables, sino como signos
'(3 1 4 pi)

> (list 3 1 4 pi)
'(3 1 4 3.141592653589793)

; EJEMPLO DE LET*
(let* ((x (* 5.0 5.0))
 (y (- x (* 4.0 4.0))))
 (sqrt y)) ⇒ 3.0

;DIFERENCIA ENTRE LET Y LETREC

(letrec ((sum (lambda (ls)
 (if (null? ls)
 0;                              letrec nos permite utilizar la funcion (en este caso sum) fuera del cuerpo de let
 (+ (car ls) (sum (cdr ls))))))); 
 (sum '(1 2 3 4 5)))

(let ((sum (lambda (ls)
 (if (null? ls);           esta funcion tira error
 0
 (+ (car ls) (sum (cdr ls)))))))
 (sum '(1 2 3 4 5)))

;/////////////////////
; VECTORES

;make
(make-vector 0) ⇒ #()
• (make-vector 0 'a) ⇒ #()
• (make-vector 5 'a) ⇒ #(a a a a a)
;lenght
• (vector-length #()) ⇒ 0
• (vector-length #(a b c)) ⇒ 3
• (vector-length (vector 1 2 3 4)) ⇒ 4
• (vector-length (make-vector 300)) ⇒ 300
;ref
•(vector-ref #(a b c) 0) ⇒ a
• (vector-ref #(a b c) 1) ⇒ b
• (vector-ref #(x y z w) 3) ⇒ w
;set! (reemplaza el valor de una dada posicion por otro)
(let ((v (vector 'a 'b 'c 'd 'e)))
 (vector-set! v 2 'x)
 v) ⇒ #(a b x d e)
;mas cosas
•(vector-fill! vector1 obj ); reemplaza cadaelemento del vector1 obj
• (vector->list vector1); devuelve una lista apartir de un vector
• (list->vector list1); convierte una lista envector

;//////////

;MAPA

                                      ;MAP: aplica el procedimiento a cadaelemento de la lista
• (map (lambda (x) (+ x 2)) '(1 2 3)); y devuelve una lista con los resultados.
→ (3 4 5)

;////////////////////

;FOR EACH

 
• (for-each display       ;FOR-EACH: aplica el procedimiento a cada elemento de la lista pero devuelve <void>.
 (list "un" "dos " "tres")) 

