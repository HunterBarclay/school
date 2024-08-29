#!/bin/guile
!#

;;
;; Assignment:  LA1
;; Author:      Hunter Barclay
;; Date:        Aug. 28th, 2024
;; Course:      cs354
;;
;; This is the testing suite for the `super-duper` function. This script
;; runs a number of tests, printing our their output, expected result, and
;; if the particular test passes.
;;

(load "super-duper.scm")

(define (test source count expected)
    (define (display-test actual)
        (format
            #t
            "┬─ Test -> (super-duper ~a ~a)\n├─ Output -> ~a\n├─ Expected -> ~a\n│\n"
            source
            count
            actual
            expected
        )
        (if (equal? actual expected)
            (display "└─ \u001B[92;1mPassed\u001B[0m\n")
            (display "└─ \u001B[91;1mFailed\u001B[0m\n")
        )
        (newline)
    )
    (display-test (super-duper source count))    
)

(test '() 1 '())
(test 'x 1 'x)
(test '(1) 2 '(1 1))
(test '(1) 3 '(1 1))

