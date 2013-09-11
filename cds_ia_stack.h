/*!
 * \file            cds_ia_stack.h
 * \brief           Interface to integer array stack functions.
 * \author          Paul Griffiths
 * \copyright       Copyright 2013 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */


#ifndef PG_CDS_STACK_INT_ARRAY_H
#define PG_CDS_STACK_INT_ARRAY_H


#include <stddef.h>
#include <stdbool.h>


/*!
 * \brief           Typedef for stack pointer.
 */

typedef struct ia_stack_t * ia_stack;


/*  Function prototypes  */

ia_stack ia_stack_init(const size_t size);
void ia_stack_free(ia_stack stk);
bool is_stack_isempty(const ia_stack stk);
bool ia_stack_isfull(const ia_stack stk);
int ia_stack_peek(const ia_stack stk);
int ia_stack_pop(ia_stack stk);
void ia_stack_push(ia_stack stk, const int n);


#endif          /*  PG_CDS_STACK_INT_ARRAY_H  */
