/*!
 * \file            da_stack.c
 * \brief           Implementation of doubleeger array stack functions.
 * \author          Paul Griffiths
 * \copyright       Copyright 2013 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */


#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <paulgrif/chelpers.h>
#include "cds_da_stack.h"


/*!
 * \brief           Struct to hold an double array stack.
 */

typedef struct da_stack_t {
    double * stack;         /*!< A pointer to the array */
    size_t length;          /*!< The length of the array */
    size_t top;             /*!< The index for the top of the stack */
} da_stack_t;


/*!
 * \brief           Constructs and initializes a new stack.
 * \param size      The initial size of the new stack.
 * \returns         A pointer to the new stack.
 */

da_stack da_stack_init(const size_t size) {
    da_stack new_stack = term_malloc(sizeof(*new_stack));
    new_stack->stack = term_malloc(sizeof(double) * size);
    new_stack->length = size;
    new_stack->top = 1;

    return new_stack;
}


/*!
 * \brief           Destructs and frees a stack.
 * \param stk       A pointer to the stack.
 */

void da_stack_free(da_stack stk) {
    free(stk->stack);
    free(stk);
}


/*!
 * \brief           Checks if a stack is empty.
 * \param stk       A pointer to the stack.
 * \returns         `true` is the stack is empty, `false` otherwise.
 */

bool is_stack_isempty(const da_stack stk) {
    return (stk->top == 0) ? true : false;
}


/*!
 * \brief           Checks if a stack is full.
 * \param stk       A pointer to the stack.
 * \returns         `true` is the stack is full, `false` otherwise.
 */

bool da_stack_isfull(const da_stack stk) {
    return (stk->top == 0) ? true : false;
}


/*!
 * \brief           Returns the top element of the stack without popping it.
 * \param stk       A pointer to the stack.
 * \returns         The value of the element at the top.
 */

double da_stack_peek(const da_stack stk) {
    return stk->stack[stk->top];
}


/*!
 * \brief           Pops the top element of the stack.
 * \param stk       A pointer to the stack.
 * \returns         The popped element of the stack.
 */

double da_stack_pop(da_stack stk) {
    return stk->stack[stk->top--];
}


/*!
 * \brief           Pushes an element onto the stack.
 * \details         If the stack is full, this function attempts to
 * reallocate memory for the array. Each time the stack is full, the
 * amount of memory requested is double the original amount.
 * \param stk       A pointer to the stack.
 * \param f         The value to push onto the stack.
 */

void da_stack_push(da_stack stk, const double f) {
    if ( stk->top == stk->length -1 ) {
        stk->stack = term_realloc(stk->stack, stk->length * 2);
        stk->length *= 2;
    }

    stk->stack[++stk->top] = f;
}
