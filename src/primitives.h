/*
 * Simple lisp parser
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

#ifndef __PRIMITIVES_H__
#define __PRIMITIVES_H__

#include <stdint.h>
#include "lisp-types.h"

/**
 * gc malloc replacements
 */
extern void *safe_malloc(size_t size);
extern char *safe_strdup(char *str);

/**
 * utilities to build primitive types
 */
extern lisp_value_t *lisp_create_type(void *value, lisp_type_t type);
extern lisp_value_t *lisp_create_pair(lisp_value_t *car, lisp_value_t *cdr);
extern lisp_value_t *lisp_create_string(char *value);
extern lisp_value_t *lisp_create_symbol(char *value);
extern lisp_value_t *lisp_create_float(double value);
extern lisp_value_t *lisp_create_int(int64_t value);
extern lisp_value_t *lisp_create_bool(int value);


#endif /* __PRIMITIVES_H__ */
