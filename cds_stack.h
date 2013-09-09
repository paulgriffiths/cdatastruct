/*!
 * \file            cds_stack.h
 * \brief           User interface to stack data structure
 * \author          Paul Griffiths
 * \copyright       Copyright 2013 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */


#ifndef PG_CDS_STACK_H
#define PG_CDS_STACK_H

#include <stddef.h>
#include <stdbool.h>

/*!
 * \brief           Typedef for stack pointer.
 */

typedef struct sl_list_t * stack;


/*  Function declarations  */

#ifdef __cplusplus
extern "C" {
#endif

stack stack_init(void (*free_func)(void *));
void stack_free(stack stk);
size_t stack_length(const stack stk);
bool stack_isempty(const stack stk);
void * stack_pop(stack stk);
void * stack_peek(stack stk);
void stack_push(stack stk, void * data);

void stack_lock(stack stk);
void stack_unlock(stack stk);

#ifdef __cplusplus
}
#endif


#endif          /*  PG_CDS_STACK_H  */
