#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "lisp-types.h"
#include "primitives.h"
#include "selfcheck.h"

int test_string_parsing(void *scaffold) {
    lv_t *result;

    result = L_CAR(lisp_parse_string("\"this is a string\""));

    assert(result->type == l_str);
    assert(strcmp(L_STR(result), "this is a string") == 0);
    return 1;
}

int test_int_parsing(void *scaffold) {
    lv_t *result;

    result = L_CAR(lisp_parse_string("7"));

    assert(result->type == l_int);
    assert(int_value(result) == 7);
    return 1;
}

int test_float_parsing(void *scaffold) {
    lv_t *result;

    result = L_CAR(lisp_parse_string("1."));

    assert(result->type == l_float);
    assert(float_value(result) == 1.0);

    /* have to use an exactly representable number! */
    result = L_CAR(lisp_parse_string(".125"));

    assert(result->type == l_float);
    assert(float_value(result) == 0.125);
    return 1;
}

int test_bool_parsing(void *scaffold) {
  lv_t *result;

  result = L_CAR(lisp_parse_string("#t"));

  assert(result->type == l_bool);
  assert(L_BOOL(result) == 1);

  result = L_CAR(lisp_parse_string("#f"));
  assert(result->type == l_bool);
  assert(L_BOOL(result) == 0);
  return 1;
}

int test_sym_parsing(void *scaffold) {
    lv_t *result;

    result = L_CAR(lisp_parse_string("aks..."));
    assert(result->type == l_sym);
    assert(strcmp(L_SYM(result), "aks...") == 0);
    return 1;
}

int test_list_parsing(void *scaffold) {
    lv_t *result;
    result = L_CAR(lisp_parse_string("()"));
    assert(result->type == l_null);

    result = L_CAR(lisp_parse_string("(1)"));
    assert(result->type == l_pair);
    assert(L_CAR(result)->type == l_int);
    assert(int_value(L_CAR(result)) == 1);
    assert(L_CDR(result) == NULL);

    result = L_CAR(lisp_parse_string("(1 . ())"));
    assert(result->type == l_pair);
    assert(L_CAR(result)->type == l_int);
    assert(int_value(L_CAR(result)) == 1);
    assert(L_CDR(result) == NULL);

    result = L_CAR(lisp_parse_string("(1 . 1)"));
    assert(result->type == l_pair);
    assert(L_CAR(result)->type == l_int);
    assert(L_CDR(result)->type == l_int);
    assert(int_value(L_CAR(result)) == 1);
    assert(int_value(L_CDR(result)) == 1);

    result = L_CAR(lisp_parse_string("(1 1)"));
    assert(result->type == l_pair);
    assert(L_CAR(result)->type == l_int);
    assert(L_CDR(result)->type == l_pair)
    assert(L_CAR(L_CDR(result))->type == l_int);;
    assert(L_CDR(L_CDR(result)) == NULL);
    assert(int_value(L_CAR(result)) == 1);
    assert(int_value(L_CAR(L_CDR(result))) == 1);


    result = L_CAR(lisp_parse_string("(1 . (1 . ()))"));
    assert(result->type == l_pair);
    assert(L_CAR(result)->type == l_int);
    assert(L_CDR(result)->type == l_pair)
    assert(L_CAR(L_CDR(result))->type == l_int);;
    assert(L_CDR(L_CDR(result)) == NULL);
    assert(int_value(L_CAR(result)) == 1);
    assert(int_value(L_CAR(L_CDR(result))) == 1);
    return 1;
}
