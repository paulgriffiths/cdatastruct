/*!
 * \file            stack.c
 * \brief           Implementation of stack data structure.
 * \details         Implemented in terms of a singly linked, singled-ended
 * list data structure.
 * \author          Paul Griffiths
 * \copyright       Copyright 2013 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */


#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include "cds_stack.h"
#include "sl_list.h"
#include "cds_common.h"


/*!
 * \brief           Initializes a new stack.
 * \param free_func A pointer to a function a free a stack node. The
 * function should return no value, and accept a `void` pointer to a
 * node. If `NULL` is specified, the standard `free()` function is used.
 * \returns         A pointer to the new stack.
 */

stack stack_init(void (*free_func)(void *)) {
    return sl_list_init(NULL, free_func);
}


/*!
 * \brief           Frees memory and releases resources used by a stack.
 * \param stk       A pointer to the stack.
 */

void stack_free(stack stk) {
    sl_list_free(stk);
}


/*!
 * \brief           Gets the number of items in a stack.
 * \param stk       A pointer to the stack.
 * \returns         The number of items in the stack.
 */

size_t stack_length(const stack stk) {
    return sl_list_length(stk);
}


/*!
 * \brief           Checks if a stack is empty.
 * \param stk       A pointer to the stack.
 * \returns         `true` is the stack is empty, `false` if not.
 */

bool stack_isempty(const stack stk) {
    return sl_list_isempty(stk);
}


/*!
 * \brief           Pops a data item from the stack.
 * \details         The item returned was previously allocated using
 * `malloc()`, so the user must `free()` the returned pointer when done.
 * \param stk       A pointer to the stack.
 * \returns         A `void` pointer to the popped data item.
 */

void * stack_pop(stack stk) {
    sl_list_node popped_node = sl_list_remove_at(stk, 0);
    void * data = popped_node->data;
    free(popped_node);
    return data;
}


/*!
 * \brief           Pushes a data item onto the stack.
 * \details         The provided pointer should point to dynamically
 * allocated memory.
 * \param stk       A pointer to the stack.
 * \param data      A pointer to the data item to be pushed.
 */

void stack_push(stack stk, void * data) {
    sl_list_prepend(stk, data);
}


/*!
 * \brief           Locks a stack's mutex.
 * \param stk       A pointer to the stack.
 */

void stack_lock(stack stk) {
    sl_list_lock(stk);
}


/*!
 * \brief           Unlocks a stack's mutex.
 * \param stk       A pointer to the stack.
 */

void stack_unlock(stack stk) {
    sl_list_unlock(stk);
}
