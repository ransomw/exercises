#lang racket

(require minikanren)

(define succeed (== #t #t))
(define fail (== #t #f))
(define else succeed)

;; reasoned schemer #s and #u definitions
(current-readtable
  (make-readtable (current-readtable)
                  #\s
                  'dispatch-macro
                  (lambda (a b c d e f) succeed)))
(current-readtable
  (make-readtable (current-readtable)
                  #\u
                  'dispatch-macro
                  (lambda (a b c d e f) fail)))

