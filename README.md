# minischeme #

[![Build Status](https://travis-ci.org/rpedde/minischeme.png?branch=master)](https://travis-ci.org/rpedde/minischeme)

Playing around with building a r5rs-ish scheme.  In addition to being
a stupid re-implementation of the wheel, it also suffers from not
being very round.

That said, this is general status toward a r[57]ish scheme:

## equivalence predicates ##

* [ ] eqv?
* [ ] eq?
* [ ] equal?

## numeric ##

* [X] integer?
* [X] float?

* [X] exact?
* [X] inexact?

* [ ] zero? (library)
* [ ] positive? (library)
* [ ] negative? (library)
* [ ] odd? (library)
* [ ] even? (library)

* [ ] max (library)
* [ ] min (library)
* [X] >
* [X] <
* [X] <=
* [X] >=
* [X] =

* [X] +
* [X] *
* [X] -
* [X] /

* [ ] abs (library)
* [X] quotient
* [X] remainder
* [X] modulo

* [ ] gcd (library)
* [ ] lcm (library)

* [X] floor
* [X] ceiling
* [X] truncate
* [X] round

* [ ] exp
* [ ] log
* [ ] sin
* [ ] cos
* [ ] tan
* [ ] asin
* [ ] acos
* [ ] atan
* [ ] sqrt
* [ ] expt

* [ ] number->string
* [ ] string->number

## boolean ##

* [X] not
* [ ] boolean?

## pairs and lists ##

* [X] pair?
* [X] cons
* [X] car
* [X] cdr
* [X] set-car!
* [X] set-cdr
* [X] caar/cadr -- cdddar/cddddr (library)
* [X] null?
* [X] list? (library?)
* [ ] list (library)
* [X] length (library?)
* [ ] append (library)
* [ ] reverse (library)
* [ ] tail-list (library)
* [ ] list-ref (library)
* [ ] memq (library)
* [ ] memv (library)
* [ ] member (library)
* [ ] assq (library)
* [ ] assv (library)
* [ ] assoc (library)

## symbols ##

* [X] symbol?
* [ ] symbol->string
* [ ] string->symbol

## chars ##

* [X] char?
* [X] char=?
* [X] char<?
* [X] char>?
* [X] char<=?
* [X] char>=?

* [ ] char-ci=? (library)
* [ ] char-ci<? (library)
* [ ] char-ci>? (library)
* [ ] char-ci<=? (library)
* [ ] char-ci>=? (library)

* [ ] char-alphabetic? (library)
* [ ] char-numeric? (library)
* [ ] char-whitespace? (library)
* [ ] char-upper-case? (library)
* [ ] char-lower-case? (library)

* [X] char->integer
* [ ] integer->char

* [ ] char-upcase (library)
* [ ] char-downcase (library)

## strings ##

* [X] string?

* [ ] make-string

* [ ] string (library)
* [ ] string-length
* [ ] string-ref
* [ ] string-set!

* [ ] string=? (library)
* [ ] string-ci=? (library)

* [ ] string<? (library)
* [ ] string>? (library)
* [ ] string<=? (library)
* [ ] string>=? (library)
* [ ] string-ci<? (library)
* [ ] string-ci>? (library)
* [ ] string-ci<=? (library)
* [ ] string-ci>=? (library)

* [ ] substring (library)
* [ ] string-append (library)

* [ ] string->list (library)
* [ ] list->string (library)

* [ ] string-copy (library)
* [ ] string-fill! (library)

## control ##

* [ ] procedure?
* [ ] apply
* [ ] map (library)
* [ ] for-each (library)
* [ ] force (library)
* [ ] call-with-current-continuation
* [ ] values
* [ ] call-with-values
* [ ] dynamic-wind

## eval ##

* [ ] eval
* [X] scheme-report-environment
* [X] null-environment
* [ ] interaction-environment

## ports ##

* [ ] call-with-input-file (library)
* [ ] call-with-output-file (library)
* [ ] input-port?
* [ ] output-port?
* [ ] current-input-port
* [ ] with-input-from-file
* [ ] with-output-to-file
* [ ] open-input-file
* [ ] open-output-file
* [ ] close-input-port
* [ ] close-output-port

## input ##

* [ ] read
* [ ] read-char
* [ ] peek-char
* [ ] eof-object?
* [ ] char-ready?

## output ##

* [ ] write (machine-readable)
* [X] display (human readable) [ not quite right... ]
* [ ] newline
* [ ] write-char

## conditional ##

* [ ] and (library)
* [ ] or (library)
* [X] if

## system interface ##

* [X] load
* [ ] transcript-on
* [ ] transcript-off

## SRFI-69 ##

* [ ] make-hash-table
* [ ] hash-table?
* [ ] alist->hash-table

* [ ] hash-table-equivalence-function
* [ ] hash-table-hash-function

* [ ] hash-table-ref
* [ ] hash-table-ref/default
* [ ] hash-table-set!
* [ ] hash-table-delete!
* [ ] hash-table-exists?
* [ ] hash-table-update!
* [ ] hash-table-update!/default

* [ ] hash-table-size
* [ ] hash-table-keys
* [ ] hash-table-values
* [ ] hash-table-walk
* [ ] hash-table-fold
* [ ] hash-table->alist
* [ ] hash-table-copy
* [ ] hash-table-merge!

* [ ] hash
* [ ] string-hash
* [ ] string-ci-hash
* [ ] hash-by-identity
