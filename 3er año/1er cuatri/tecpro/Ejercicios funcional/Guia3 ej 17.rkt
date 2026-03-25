#| 17)Se desea crear un programa que permita convertir un lote de datos de un formato a
otro. Los datos llegan en formato de lista de listas, donde el primer elemento
determina el contenido de la lista y el segundo tiene la lista de datos. Los datos
pueden venir en formato texto, decimal o booleano y se desea obtener una lista
igual pero con todos sus componentes en formato decimal y todos positivos.
(convdatos '(
("D" (1 2 3 4 5))
("T" ("6" "7" "8"))
("B" ("V" "F"))
) —----> '((1 2 3 4 5) (6 7 8) (1 0))|#

; Función auxiliar para convertir texto a decimal
(define (convertir-texto-a-decimal str)
  (string->number str))

; Función auxiliar para convertir booleano a decimal
(define (convertir-booleano-a-decimal bool)
  (if (eqv? bool "V") 1 0))

; Función auxiliar para convertir una sublista según su tipo
(define (convertir-sublista tipo datos)
  (cond
    [(equal? tipo "D") datos]
    [(equal? tipo "T") (map convertir-texto-a-decimal datos)]
    [(equal? tipo "B") (map convertir-booleano-a-decimal datos)]))

; Función principal para convertir los datos del lote
(define (convdatos l)
  (map (lambda (l)
         (let ((tipo (car l))
               (datos (cadr l)))
           (convertir-sublista tipo datos)))
       l))

; Ejemplo de uso
(convdatos '(
  ("D" (1 2 3 4 5))
  ("T" ("6" "7" "8"))
  ("B" ("V" "F"))
))
; Resultado esperado: '((1 2 3 4 5) (6 7 8) (1 0))
