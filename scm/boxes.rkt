#lang racket

(define my-box (box '()))

(set-box! my-box 13)

(unbox my-box)
