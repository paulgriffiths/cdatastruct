/*!
 * \file            cds_da_stack.h
 * \brief           Interface to double array stack functions.
 * \author          Paul Griffiths
 * \copyright       Copyright 2013 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */


#ifndef PG_CDS_STACK_DOUBLE_ARRAY_H
#define PG_CDS_STACK_DOUBLE_ARRAY_H


#include <stddef.h>
#include <stdbool.h>


/*!
 * \brief           Typedef for stack pointer.
 */

typedef struct da_stack_t * da_stack;


/*  Function prototypes  */

da_stack da_stack_init(const size_t size);
void da_stack_free(da_stack stk);
bool is_stack_isempty(const da_stack stk);
bool da_stack_isfull(const da_stack stk);
double da_stack_peek(const da_stack stk);
double da_stack_pop(da_stack stk);
void da_stack_push(da_stack stk, const double n);


#endif          /*  PG_CDS_STACK_DOUBLE_ARRAY_H  */
