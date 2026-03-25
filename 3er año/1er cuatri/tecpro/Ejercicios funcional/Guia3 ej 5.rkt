#lang racket

(let ([a 1][b 2])

 (let ([c (/ (* 7 a) b)])

  (+ c c (* c (/ 3 7)))))


(let ([l (list 'a 'b 'c)])
  (cons (car l) (cdr l)))
