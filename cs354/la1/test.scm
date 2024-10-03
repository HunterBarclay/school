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

;; Loads `super-duper` script.
(load "super-duper.scm")

;; Executes `super-duper` with the provided inputs source and count, then
;; checks the output against expected, printing the results of the test
;; to the console accordingly.
;;
;; Parameters:
;;     source   - Source to test.
;;     count    - Number of duplication in the test.
;;     expected - Exepcted output of `super-duper`.
(define (test source count expected)
    (define (display-test actual)
        (format
            #t
            "┬─ Test ->\t(super-duper ~a ~a)\n├─ Output ->\t~a\n├─ Expected ->\t~a\n│\n"
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

(display "Examples from assignment instructions\n")
(test
    123 1
    123
)
(test
    123 2
    123
)
(test
    '() 1
    '()
)
(test
    '() 2
    '()
)
(test
    '(x) 1
    '(x)
)
(test
    '(x) 2
    '(x x)
)
(test
    '(x y) 1
    '(x y)
)
(test
    '(x y) 2
    '(x x y y)
)
(test
    '((a b) y) 3
    '((a a a b b b) (a a a b b b) (a a a b b b) y y y)
)

(display "Additional Test(s)\n")
(test
    '((a b) ((x) y z)) 3
    '((a a a b b b) (a a a b b b) (a a a b b b) ((x x x) (x x x) (x x x) y y y z z z) ((x x x) (x x x) (x x x) y y y z z z) ((x x x) (x x x) (x x x) y y y z z z))
)
(test
    '(a) 13
    '(a a a a a a a a a a a a a)
)

