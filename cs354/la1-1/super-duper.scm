;;
;; Assignment:  LA1
;; Author:      Hunter Barclay
;; Date:        Aug. 28th, 2024
;; Course:      cs354
;;
;; This script contains the `super-duper` function, along with
;; helper functions to perform the duplications.
;;

;; Determine if a variable is an atom. A.k.a, is the variable
;; null or not a pair?
(define (atom? var)
    (or (null? var) (not (pair? var)))
)

;; Combine two lists. This function works by chopping the left
;; list up, element to element, appending each to whatever is
;; currently on the right, until there is nothing left in left,
;; in which case, right is returned.
(define (merge left right)
    (if (null? left)
        right
        (cons (car left) (merge (cdr left) right))    
    )
)

;; Duplicates item, count times into a list.
(define (duper item count)
    (if (< count 1)
        '()
        (cons item (duper item (- count 1)))
    )
)

;; Duplicates each element within the list source, count times.
;; Will run super-duper recursively on elements within source that
;; are also lists.
(define (super-duper source count)
    (if (atom? source)
        source
        (if (pair? (car source))
            (merge (duper (super-duper (car source) count) count) (super-duper (cdr source) count))
            (merge (duper (car source) count) (super-duper (cdr source) count))
        )
    )
)

