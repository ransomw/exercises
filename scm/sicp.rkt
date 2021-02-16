#lang racket

;; ??? no redefines?

;; (require racket/help)

(define x 11)

;;;


(define (square x) (* x x))

(define (sum-of-squares a b)
  (+ (square a) (square b)))

(define (abs x)
  (cond ((> x 0) x)
        (else (- x))))

(define (average a b)
  (/ (+ a b) 2))

(define (sqrt x)
  (define (good-enough? guess)
    (< (abs (- (square guess) x)) 0.001))
  ;; newton's method converges since improve
  ;; is a contraction map
  (define (improve guess)
    (average guess (/ x guess)))
  (define (sqrt-iter guess)
    (if (good-enough? guess)
        guess
        (sqrt-iter (improve guess))))
  (sqrt-iter 1.0))

;; note the number of repeated computations
;; in the recursive form of fibonnaci numbers
(define (fib-rec n)
  (cond ((< n 0) n)
        ((= n 0) 0)
        ((= n 1) 1)
        (else (+ (fib-rec (- n 1))
                 (fib-rec (- n 2))))))

(define (fib n)
  (define (fib-iter acc-a acc-b cnt)
    (if (= cnt n)
        acc-a
        (fib-iter (+ acc-a acc-b) acc-a (+ cnt 1))))
  (fib-iter 1 0 0))

;; todo: iterative implementation using dynamic programming
(define (count-change total-amount)
  (define (cc amount kinds-of-coins)
    (cond ((= amount 0) 1)
          ((or (< amount 0) (= kinds-of-coins 0)) 0)
          (else (+ (cc amount
                       (- kinds-of-coins 1))
                   (cc (- amount
                          (first-denomination kinds-of-coins))
                       kinds-of-coins)))))
  (define (first-denomination k)
    (cond ((= k 1) 1)
          ((= k 2) 5)
          ((= k 3) 10)
          ((= k 4) 25)
          ((= k 5) 50)))
  (cc total-amount 5))


;; note here that `remainder` is a builtin
(define (even? n)
  (= (remainder n 2) 0))

;; euclid's algorithm for the record
;; relies on GCD(a, b) = GCD(b, a|b)
(define (gcd a b)
  (if (= b 0)
      (abs a)
      (gcd b (remainder a b))))

;;; 1.3

(define (cube x) (* x x x))

(define (sum-integers-naive a b)
  (if (> a b)
      0
      (+ a (sum-integers-naive (+ a 1) b))))

(define (sum-cubes-naive a b)
  (if (> a b)
      0
      (+ (cube a) (sum-cubes-naive (+ a 1) b))))

;; idenitity is already defined in Racket
;; (define (identity x) x)
(define (inc x) (+ x 1))
(define (sum term a next b)
  (if (> a b)
      0
      (+ (term a) (sum term (next a) next b))))

(define (sum-integers a b)
  (sum identity a inc b))

(define (sum-cubes a b)
  (sum cube a inc b))

(define (pi-sum a b)
  (define (pi-term x)
    (/ 1.0 (* x (+ x 2))))
  (define (pi-next x)
    (+ x 4))
  (sum pi-term a pi-next b))
(define pi-approx (* 8 (pi-sum 1 1000)))

;;; 2.1

;; this chapter is about data abstraction,
;; the use of symbolic rather than concrete
;; numeric or otherwise literal data.
;; the idea is to not dwell on how data is
;; literally represented and instead
;; understand the interface to the data.
;;
;; probably the most ubiquitous interface
;; in scheme is that of `cons` pairs.
;; these are instantiated via a
;; /constructor/, `cons`
(define a-pair (cons 1 2))
;; and accessed via /selectors/,
;; `car` and `cdr`, which return the
;; first and second elements of the pair:
(car a-pair) ;; => 1
(cdr a-pair) ;; => 2

;; it's possible to implement `cons`
;; pairs in a variety of ways.  here's one
(define (alt-cons x y)
  (define (dispatch m)
    (cond ((= m 0) x)
          ((= m 1) y)
          (else (error "arg must be 0 or 1"))))
  dispatch)
(define (alt-car x) (x 0))
(define (alt-cdr x) (x 1))

;; the above functions fulfill the same
;; guarantees as the builtins:
(define b-pair (alt-cons 1 2))
;; and accessed via /selectors/,
;; `car` and `cdr`, which return the
;; first and second elements of the pair:
(alt-car b-pair) ;; => 1
(alt-cdr b-pair) ;; => 2
;; in the abstract, the data is the same,
;; independent of the internal representation.

;; aside from being representation-
;; -independent, data abstraction occurs
;; in layers.  here's an implementation
;; of rational numbers (fractions) with
;; two layers.

;;
;; the first layer ;;
;;
;; need (1) create rational
;; numbers and access (2) numerator and
;; (3) denominators.

;; fractions are pairs of numbers.
;; a sketch of the desired functionality
;; might look something like
(define (naive-make-rat n d) (cons n d)) ;; (1)
(define (naive-numer rat) (car rat)) ;; (2)
(define (naive-denom rat) (cdr rat)) ;; (3)



;; however, to make this layer more
;; user-friendly, we might add in
;; functionality to simplify the fraction
;; and prevent zero denominators
(define (simplified-rat n d)
  (define (sign x)
    (cond ((< x 0) -1)
          ((> x 0) 1)
          (else 0)))
  (when (= 0 d)
    (error "no zero denominators"))
  (let ((g (gcd n d)))
    (cons (* (* (sign n) (sign d))
             (/ (abs n) g))
          (/ (abs d) g))))

;; then we can write an interface
;; that uses the simplification functionality
;; in the constructor
(define make-rat simplified-rat) ;; (1)
(define (numer rat) (car rat)) ;; (2)
(define (denom rat) (cdr rat)) ;; (3)

;; or in the selectors
(define (make-rat-alt n d) (cons n d)) ;; (1)
(define (simplify-rat rat)
  (simplified-rat (car rat)
                  (cdr rat)))
;; (2)
(define (numer-alt rat)
  (car (simplify-rat rat)))
;; (3)
(define (denom-alt rat)
  (cdr (simplify-rat rat)))

;; ..so whether we simplify the
;;   fraction on creation of the
;;   data structure or on access,
;;   the interface remains the same.

;;
;; the second layer ;;
;;
;; an additional layer
;; of abstraction uses the first layer
;; to provide operations on rational
;; numbers.
;;

(define (add-rat x y)
  (make-rat (+ (* (numer x) (denom y))
               (* (numer y) (denom x)))
            (* (denom x) (denom y))))
(define (sub-rat x y)
  (make-rat (- (* (numer x) (denom y))
               (* (numer y) (denom x)))
            (* (denom x) (denom y))))
(define (mul-rat x y)
  (make-rat (* (numer x) (numer y))
            (* (denom x) (denom y))))
(define (div-rat x y)
  (make-rat (* (numer x) (denom y))
            (* (denom x) (numer y))))
(define (equal-rat? x y)
  (= (* (numer x) (denom y))
     (* (numer y) (denom x))))

;; .. we could then imagine an additional
;; application layer

;;; 2.2

;; `cons` pairs are fundamental to many
;; lisp data structures.  lists are
;; represented as sequences of cons pairs.
;; for instance
(equal?
 (list 1 2 3)
 (cons 1 (cons 2 (cons 3 null)))) ;; => #t
;; and all kinds of other data structures
;; can be made from cons.
(cons (cons 1 2)
      (cons 3 4))
(cons 1 (cons 2 3))
;; and so on.

;; despite the previous section on data
;; abstraction, it's common to operate
;; on lists using `car` and `cdr`
(car (list 1 2 3)) ;; => 1
(cdr (list 1 2 3)) ;; => (2 3)
;; i.e. there aren't special functions
;; such as `head` and `tail` for lists,
;; and `cons` is often used to add elements
;; to lists
(equal?
 (cons 1 (list 2 3))
 (list 1 2 3)) ;; => #t

;; here's an example of
;; writing list abstractions with
;; cons operations
(define (list-ref l n)
  (if (= n 0)
      (car l)
      (list-ref (cdr l) (- n 1))))
(define nth list-ref)
(nth (list 1 2 3) 2) ;; => 3

;; and there are some builtins as well
(length (list 1 2)) ;; => 2
(append (list 1) (list 2)) ;; => (1 2)
;; here are a few ways to write the
;; builtins from scratch
(define (length-recurse l)
  (if (null? l)
      0
      (inc (length-recurse (cdr l)))))
(define (length-iter l)
  (define (li l n)
    (if (null? l)
        n
        (li (cdr l) (inc n))))
  (li l 0))
(define (append-recurse l-one l-two)
  (if (null? l-one)
      l-two
      (cons (car l-one)
            (append (cdr l-one) l-two))))
;; ?? append-iter?
(length-recurse (list 1 2)) ;; => 2
(length-iter (list 1 2)) ;; => 2
(append-recurse (list 1) (list 2)) ;; => (1 2)

;; e2.17
;; return the last element of a nonempty list
(define (last-pair l)
  (if (null? (cdr l))
      (car l)
      (last-pair (cdr l))))
(last-pair (list 1 2 3)) ;; => 3

;; e2.18
;; reverse a list
(define (reverse-alt l)
  (define (it l o)
    (if (null? l)
        o
        (it (cdr l) (cons (car l) o))))
  (it l (list)))
(reverse-alt (list 1 2 3 4)) ;; => (4 3 2 1)

;; e...

;;
;; the ability to pass functions as
;; arguments is a pretty important idea.
;;
;; consider the following function
;; that multiplies each item in a list
;; by some constant factor
(define (scale-items-naive c l)
  (if (null? l)
      l
      (cons (* c (car l))
            (scale-items-naive
             c (cdr l)))))
(scale-items-naive 2 (list 3 4)) ;; => (6 8)
;; now, if we want to add some
;; constant factor -- of in fact,
;; perform any operation on every element
;; of the list -- it would be convenient
;; not to have to re-write list operations
;; in the previous proceedure.

;; so we abstract out the list operations
(define (map-alt fn l)
  (if (null? l)
      l
      (cons (fn (car l))
            (map-alt
             fn (cdr l)))))
;; and write the proceedure by passing
;; a function argument.
(define (scale-items c l)
  (map-alt (lambda (x) (* x c)) l))
;; ... there's a bunch of terminology
;;   surrounding the idea of passing
;;   function arguments, although this
;;   example mostly covers the core idea.
;; in practice, the abstractions surrounding
;; the idea can become complex.

;; functional abstraction aside and back
;; to data structures, another data structure
;; we can implement with cons pairs is trees.
(define tree-one
  (cons (list 1 2) (list 3 4)))

;; of course, without constructors and selectors
;; the interpretation of concrete data as a
;; tree structure isn't altogether obvious.
;;
;; here're a few ways we could reshape the
;; definition
(equal?
 (cons
  (cons
   1
   (cons
    2
    '()))
  (cons
   3
   (cons
    4
    '())))
 tree-one) ;; => #t

(equal?
 (list (cons 1 (cons 2 '())) 3 4)
 tree-one) ;; => #t

(equal?
 (list (list 1 2) 3 4)
 tree-one) ;; => #t

;; with the last being the desired
;; interpretation
;;
;;  tree-one
;; |       \ \
;;[node]   3 4
;; | \
;; 1  2
;;
;; where [node] is some internal node.
;; that is, a tree is a list of nested lists,
;; where each nested list creates an
;; internal node.

;; todo(?): ascii-art box diagrams

(define (count-leaves-naive t)
  (cond ((null? t) 0)
        ((list? (car t))
         (+ (count-leaves-naive
             (car t))
            (count-leaves-naive
             (cdr t))))
        (else (inc (count-leaves-naive
                    (cdr t))))))

(count-leaves-naive
 (list tree-one tree-one)) ;; => 8

(define (count-leaves t)
  (cond ((null? t) 0)
        ((not (pair? t)) 1)
        (+ (count-leaves (car t))
           (count-leaves (cdr t)))))




;;; 3.1

;; this chapter introduces the assignment
;; operator, `set!`.
;; before this chapter, functions or procedures
;; are mostly "specifications for mathematical
;; functions" where the same input always
;; produces the same output -- i.e. functions
;; were free of side-effects.

(define balance 100)

(define (withdraw amount)
  (if (<= amount balance)
      ;; `begin` evaluates each form
      ;; in sequence and evaluates to
      ;; the value of the last form.
      (begin
        ;; `set!`, the assignment operator,
        ;; changes the value bound to a symbol
        (set! balance (- balance amount))
        balance)
   "Insufficient funds"))

;; evaluating the following expression
;; now produces different values each
;; time.
;; (withdraw 20)

;; recall, using `define` within
;; a proceedure definition creates a
;; symbol scoped locally to that proceedure.
;; `define` cannot be used in place of `set!`
;; in the above definition of `withdraw`.

;; `withdraw` relies on global state stored
;; in the `balance` variable.  here's an
;; alternate implementation with local state.
(define new-withdraw
  (let ((balance 100))
    (lambda (amount)
      (if (<= amount balance)
          (begin
            (set! balance (- balance amount))
            balance)
          "Insufficient funds"))))

;; `new-withdraw` remains a singlton.
;; there's precisely one instance of the
;; object.  the following allows creating
;; multiple instances

(define (make-withdraw balance)
  (lambda (amount)
      (if (<= amount balance)
          (begin
            (set! balance (- balance amount))
            balance)
          "Insufficient funds")))

;; like so
(define W1 (make-withdraw 100))
(define W2 (make-withdraw 100))

;; s.t.
;; (W1 10)
;; and
;; (W2 10)
;; operate on independent states

;; thus far, we've introduced objects
;; with precisely one proceedure.
;; a more replete OOP metaphor may
;; include multiple proceedures per
;; object.  one methodology to construct
;; such objects is via a "dispatch" function.
(define (make-account balance)
  (define (withdraw amount)
    (if (<= amount balance)
        (begin
          (set! balance (- balance amount))
          balance)
        "Insufficient funds"))
  (define (deposit amount)
    (set! balance (+ balance amount))
    balance)
  (define (dispatch method)
    (cond ((eq? method 'deposit)
           deposit)
          ((eq? method 'withdraw)
           withdraw)
          (else
           (error
            "Unknown request -- make-account"
            method))))
  dispatch)

;; the dispatcher method
(define account (make-account 100))
;; may access the internally-defined methods
;; ((account 'withdraw) 10)
;; ((account 'deposit) 10)

;; another methodology is to construct
;; a dictionary or mapping type.
;; this methodology allows for
;; introspection -- i.e. listing
;; available methods.
(define (new-make-account balance)
  (define (withdraw amount)
    (if (<= amount balance)
        (begin
          (set! balance (- balance amount))
          balance)
        "Insufficient funds"))
  (define (deposit amount)
    (set! balance (+ balance amount))
    balance)
  (list (list 'deposit deposit)
        (list 'withdraw withdraw)))
;; todo: example use



;; Ex 3.2

(define (make-monitored fn)
  (define (car-or-null lst)
    (if (null? lst)
        null
        (car lst)))
  (let ((calls (list)))
    (lambda args
      (let ((first-arg (car-or-null args)))
        (cond
         ((eq? first-arg 'how-many-calls?)
          (length calls))
         (else
          (begin
            (set! calls (cons args calls))
            (apply fn args))))))))

(define sqrt-monitored (make-monitored sqrt))

(sqrt-monitored 4)
;; (sqrt-monitored 'how-many-calls?)



;;; 5.2

(define (make-register name)
  (let ((contents '*unassigned*))
    ;; registers are functions implementing IPC-like to either..
    (define (dispatch message)
      ;; return the contents of the register
      (cond ((eq? message 'get) contents)
            ;; or return a setter function
            ((eq? message 'set)
             (lambda (value) (set! contents value)))
            (else
             (error "Unknown request -- REGISTER" message))))
    dispatch))
;; .. crucially, note that registers are untyped
;; aand a couple of helper functions
(define (get-contents register)
  (register 'get))
(define (set-contents! register value)
  ((register 'set) value))

;; the stack is defined similarly
;; in terms of
;; - no-argument ops returning values
;; - n-ary ops returning n-ary functions
;; - the object itself being a closure
;;   over a lisp data structure (a list,
;;   in this case)
(define (make-stack)
  (let ((s '()))
    (define (push x)
      ;; ??? recall how `set!` differs from `define`?
      (set! s (cons x s)))
    (define (pop)
      (if (null? s)
          (error "Empty stack -- POP")
          ;; LYAHfgg terminology in effect
          (let ((head (car s))
                (tail (cdr s)))
            (set! s tail)
            head)))
    (define (initialize)
      (set! s '())
      'done)
    (define (dispatch message)
      (cond ((eq? message 'push) push)
            ((eq? message 'pop) (pop))
            ((eq? message 'initialize) (initialize))
            (else (error "Unknown request -- STACK"
                         message))))
    dispatch))
;; and similarly, a couple of helper functions
(define (pop stack)
  (stack 'pop))
(define (push stack value)
  ((stack 'push) value))

;; the forthcoming `make-new-machine`
;; needn't be aware of the instruction set
;; because registers, etc. are untyped, for one.
;; nonetheless, it will contain instructions.
;;
;; for the purposes of building the machine,
;; each instruction is a pair:
;; - the op name
;; - an IoC fn that's passed
;;   > the machine itself
;;   > the op name (again)
;;   > .. several other values ..
(define (make-instruction text)
  ;; use racket lang boxes instead of
  ;; r5rs cons cells because racket
  ;; doesn't have set-cdr!.
  ;; todo: write revisions in r5rs
  (cons text
        ;; read on past `make-new-machine` to understand what this value is
        (box (lambda (x) x))))
(define (instruction-text inst)
  (car inst))
(define (instruction-execution-proc inst)
  (unbox (cdr inst)))
(define (set-instruction-execution-proc! inst proc)
  (set-box! (cdr inst) proc))

(define (make-new-machine)
  (let ((pc (make-register 'pc))
        (flag (make-register 'flag))
        (stack (make-stack))
        (the-instruction-sequence '()))
    ;; consider introducing some special language
    ;; to manipulate these associative array data
    ;; structures,
    ;; ???
    ;; and use ('name . val) syntax if possible
    (let ((the-ops
           (list (list 'initialize-stack
                       (lambda () (stack 'initialize)))))
          (register-table
           (list (list 'pc pc) (list 'flag flag))))
      ;;
      (define (allocate-register name)
        (if (assoc name register-table)
            (error "Multiply defined register: " name)
            (set! register-table
              ;; todo: assoc arr dsl
              (cons (list name (make-register name))
                    register-table)))
        'register-allocated)
      (define (lookup-register name)
        (let ((val (assoc name register-table)))
          (if val
              ;; todo: assoc arr dsl
              (cadr val)
              (error "Unknown register:" name))))
      (define (execute)
        (let ((insts (get-contents pc)))
          (if (null? insts)
              'done
              (begin
                ((instruction-execution-proc (car insts)))
                (execute)))))
      ;;
      (define (dispatch message)
        ;; todo (fork): allow pausing at breakpoints
        ;;    to execute arbitrary instructions and inspect registers.
        ;; allow stepping through instructions one at a time, etc.
        (cond ((eq? message
                    'start)
               (set-contents! pc the-instruction-sequence)
               (execute))
              ((eq? message
                    'install-instruction-sequence)
               (lambda (seq) (set! the-instruction-sequence seq)))
              ;; todo: consider using a different mechanism
              ;;       to allocate registers .. or at least
              ;;       prefixing this somehow since registers
              ;;       are typically immutable in, e.g., x86 isa
              ((eq? message
                    'allocate-register)
               allocate-register)
              ((eq? message
                    'get-register)
               lookup-register)
              ((eq? message
                    'install-operations)
               (lambda (ops) (set! the-ops (append the-ops ops))))
              ((eq? message
                    'stack)
               stack)
              ((eq? message
                    'operations)
               the-ops)
              (else (error "Unknown request -- MACHINE" message))))
      dispatch)))
