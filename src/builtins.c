/*
 * Simple lisp interpreter
 *
 * Copyright (C) 2014 Ron Pedde (ron@pedde.com)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "lisp-types.h"
#include "primitives.h"
#include "builtins.h"

static lv_t *s_is_type(lv_t *v, lisp_type_t t) {
    if(v->type == t)
        return lisp_create_bool(1);
    return lisp_create_bool(0);
}

lv_t *p_nullp(lv_t *env, lv_t *v) {
    assert(v && v->type == l_pair);
    rt_assert(c_list_length(v) == 1, le_arity, "wrong arity");
    lv_t *a0 = L_CAR(v);

    return s_is_type(a0, l_null);
}

lv_t *p_symbolp(lv_t *env, lv_t *v) {
    assert(v && v->type == l_pair);
    rt_assert(c_list_length(v) == 1, le_arity, "wrong arity");
    lv_t *a0 = L_CAR(v);

    return s_is_type(a0, l_sym);
}

lv_t *p_atomp(lv_t *env, lv_t *v) {
    assert(v && v->type == l_pair);
    rt_assert(c_list_length(v) == 1, le_arity, "wrong arity");
    lv_t *a0 = L_CAR(v);

    if(a0->type != l_pair)
        return lisp_create_bool(1);
    return lisp_create_bool(0);
}

lv_t *p_consp(lv_t *env, lv_t *v) {
    assert(v && v->type == l_pair);
    rt_assert(c_list_length(v) == 1, le_arity, "wrong arity");
    lv_t *a0 = L_CAR(v);

    return s_is_type(a0, l_pair);
}

lv_t *p_listp(lv_t *env, lv_t *v) {
    assert(v && v->type == l_pair);
    rt_assert(c_list_length(v) == 1, le_arity, "wrong arity");
    lv_t *a0 = L_CAR(v);

    if((a0->type == l_pair) || (a0->type == l_null))
        return lisp_create_bool(1);
    return lisp_create_bool(0);
}

lv_t *p_pairp(lv_t *env, lv_t *v) {
    assert(v && v->type == l_pair);
    rt_assert(c_list_length(v) == 1, le_arity, "wrong arity");
    lv_t *a0 = L_CAR(v);

    return lisp_create_bool(a0->type == l_pair);
}

/**
 * c helper for equalp
 */
int c_equalp(lv_t *a1, lv_t *a2) {
    int result = 0;

    if(a1->type != a2->type)
        return 0;

    switch(a1->type) {
    case l_int:
        result = (L_INT(a1) == L_INT(a2));
        break;
    case l_float:
        result = (L_FLOAT(a1) == L_FLOAT(a2));
        break;
    case l_bool:
        if((L_BOOL(a1) == 0 && L_BOOL(a2) == 0) ||
           (L_BOOL(a1) != 0 && L_BOOL(a1) != 0))
            result = 1;
        break;
    case l_sym:
        if(strcmp(L_SYM(a1), L_SYM(a2)) == 0)
            result = 1;
        break;
    case l_str:
        if(strcmp(L_STR(a1), L_STR(a2)) == 0)
            result = 1;
        break;
    case l_hash:
        result = (L_HASH(a1) == L_HASH(a2));
        break;
    case l_null:
        result = 1;
        break;
    case l_fn:
        result = (L_FN(a1) == L_FN(a1));
        break;
    case l_pair:
        /* this is perhaps not right */
        if(!(c_equalp(L_CAR(a1), L_CAR(a2))))
            return 0;
        if(L_CDR(a1) && L_CDR(a2))
            return c_equalp(L_CDR(a1), L_CDR(a2));
        if(!L_CDR(a1) && !L_CDR(a2))
            return 1;
        result = 0;
        break;
    }

    return result;
}

/**
 * lisp wrapper around c_equalp
 */
lv_t *p_equalp(lv_t *env, lv_t *v) {
    int result;

    assert(v && v->type == l_pair);
    rt_assert(c_list_length(v) == 2, le_arity, "wrong arity");

    lv_t *a1 = L_CAR(v);
    lv_t *a2 = L_CADR(v);

    return(lisp_create_bool(c_equalp(a1, a2)));
}

/**
 * add numeric types
 */
lv_t *p_plus(lv_t *env, lv_t *v) {
    int i_result = 0;
    double f_result = 0.0;

    lv_t *current = v;
    lv_t *op;

    lisp_type_t ret_type = l_int;

    assert(v && (v->type == l_pair || v->type == l_null));

    while(current && (current->type == l_pair)) {
        op = L_CAR(current);

        rt_assert((op->type == l_int || op->type == l_float),
                  le_type, "non-numeric add");

        /* promote result, if necessary */
        if(ret_type != op->type) {
            if(ret_type == l_int) {
                ret_type = l_float;
                f_result = (float)i_result;
            }
        }

        if(ret_type == l_float) {
            if(op->type == l_int) {
                f_result += (float)L_INT(op);
            } else {
                f_result += L_FLOAT(op);
            }
        } else {
            i_result += L_INT(op);
        }

        current = L_CDR(current);
    }

    if(ret_type == l_int)
        return lisp_create_int(i_result);

    return lisp_create_float(f_result);
}

lv_t *p_set_cdr(lv_t *env, lv_t *v) {
    assert(v && (v->type == l_pair));

    rt_assert(c_list_length(v) == 2, le_arity, "set-cdr arity");
    rt_assert(L_CAR(v)->type == l_pair, le_type, "set-cdr on non-pair");

    if(L_CADR(v)->type == l_null)
        L_CDR(L_CAR(v)) = NULL;
    else
        L_CDR(L_CAR(v)) = L_CADR(v);

    return lisp_create_null();
}

lv_t *p_set_car(lv_t *env, lv_t *v) {
    assert(v && (v->type == l_pair));

    rt_assert(c_list_length(v) == 2, le_arity, "set-cdr arity");
    rt_assert(L_CAR(v)->type == l_pair, le_type, "set-car on non-pair");

    L_CAR(L_CAR(v)) = L_CADR(v);
    return lisp_create_null();
}

lv_t *p_inspect(lv_t *env, lv_t *v) {
    lv_t *arg;
    int show_line = 1;
    char buffer[256];

    assert(v && (v->type == l_pair));
    rt_assert(c_list_length(v) == 1, le_arity, "inspect arity");

    arg = L_CAR(v);
    memset(buffer, 0, sizeof(buffer));

    strcat(buffer, "type: ");

    if(arg->type == l_fn) {
        if(L_FN(arg)) {
            strcat(buffer, "built-in function");
            show_line = 0;
        } else {
            strcat(buffer, "lambda, declared at");
        }
    } else {
        strcat(buffer, lisp_types_list[arg->type] + 2);
    }

    if(show_line)
        sprintf(buffer + strlen(buffer), " %s:%d:%d",
                arg->file, arg->row, arg->col);

    if(arg->bound)
        sprintf(buffer + strlen(buffer), ", bound to: %s",
                L_SYM(arg->bound));

    return lisp_create_string(buffer);
}

lv_t *p_load(lv_t *env, lv_t *v) {
    assert(v && (v->type == l_pair));
    rt_assert(c_list_length(v) == 1, le_arity, "load arity");
    rt_assert(L_CAR(v)->type == l_str, le_type, "filename must be string");

    return c_sequential_eval(env, lisp_parse_file(L_STR(L_CAR(v))));
}

lv_t *p_length(lv_t *env, lv_t *v) {
    assert(v && v->type == l_pair);

    rt_assert(c_list_length(v) == 1, le_arity, "length arity");
    return lisp_create_int(c_list_length(L_CAR(v)));
}

lv_t *p_assert(lv_t *env, lv_t *v) {
    assert(v && v->type == l_pair);
    rt_assert(c_list_length(v) == 1, le_arity, "assert arity");
    rt_assert(L_CAR(v)->type == l_bool, le_type, "assert not bool");

    if(!L_BOOL(L_CAR(v)))
        rt_assert(0, le_internal, "error raised");

    return lisp_create_null();
}

lv_t *p_warn(lv_t *env, lv_t *v) {
    assert(v && v->type == l_pair);
    rt_assert(c_list_length(v) == 1, le_arity, "warn arity");
    rt_assert(L_CAR(v)->type == l_bool, le_type, "warn not bool");

    if(!L_BOOL(L_CAR(v)))
        rt_assert(0, le_warn, "warning raised");

    return lisp_create_null();
}

lv_t *p_not(lv_t *env, lv_t *v) {
    assert(v && v->type == l_pair);
    rt_assert(c_list_length(v) == 1, le_arity, "not arity");
    rt_assert(L_CAR(v)->type == l_bool, le_type, "not bool");

    return lisp_create_bool(!(L_BOOL(L_CAR(v))));
}

lv_t *p_car(lv_t *env, lv_t *v) {
    assert(v && v->type == l_pair);

    rt_assert(c_list_length(v) == 1, le_arity, "car arity");
    rt_assert(v->type == l_pair || v->type == l_null, le_type,
              "car on non-list");

    if(L_CAR(v)->type == l_null)
        return v;

    return L_CAAR(v);
}

lv_t *p_cdr(lv_t *env, lv_t *v) {
    assert(v && v->type == l_pair);

    rt_assert(c_list_length(v) == 1, le_arity, "car arity");
    rt_assert(v->type == l_pair || v->type == l_null, le_type,
              "car on non-list");

    if(L_CAR(v)->type == l_null || L_CDAR(v) == NULL)
        return lisp_create_null();

    return L_CDAR(v);
}

lv_t *p_cons(lv_t *env, lv_t *v) {
    assert(v && v->type == l_pair);

    rt_assert(c_list_length(v) == 2, le_arity, "cons arity");
    return lisp_create_pair(L_CAR(v), L_CADR(v));
}
