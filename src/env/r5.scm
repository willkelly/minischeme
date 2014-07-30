;
; Create r5-ish environment
;

(define #exec-success 0)
(define #exec-arity 1)
(define #exec-type 2)
(define #exec-lookup 3)
(define #exec-internal 4)
(define #exec-syntax 5)
(define #exec-system 6)
(define #exec-raise 7)
(define #exec-warn 8)

(define + p-+)
(define null? p-null?)
(define symbol? p-symbol?)
(define atom? p-atom?)
(define cons? p-cons?)
(define list? p-list?)
(define pair? p-pair?)
(define equal? p-equal?)
(define set-cdr! p-set-cdr!)
(define set-car! p-set-car!)
(define length p-length)
(define inspect p-inspect)
(define load p-load)
(define assert p-assert)
(define warn p-warn)
(define not p-not)
(define cons p-cons)
(define car p-car)
(define cdr p-cdr)
(define gensym p-gensym)
(define display p-display)
(define format p-format)

;; ports
(define open-file p-open-file)
(define port-filename p-port-filename)
(define port-set-filename! p-port-set-filename!)
(define port-mode p-port-mode)
(define file-port? p-file-port?)

;; char
(define char? p-char?)
(define char=? p-char=?)
(define char<? p-char<?)
(define char>? p-char>?)
(define char<=? p-char<=?)
(define char>=? p-char>=?)
(define char->integer p-char->integer)
