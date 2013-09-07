/*!
 * \file            queue.c
 * \brief           Implementation of queue data structure.
 * \details         Implemented in terms of a doubly linked, double-ended
 * list data structure.
 * \author          Paul Griffiths
 * \copyright       Copyright 2013 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */


#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include "cds_queue.h"
#include "dl_list.h"
#include "cds_common.h"


/*!
 * \brief           Initializes a new queue.
 * \param free_func A pointer to a function to free a queue node. The
 * function should return no value, and accept a `void` pointer to a
 * node. If `NULL` is specified, the standard `free()` function is used.
 * \returns         A pointer to the new queue.
 */

queue queue_init(void (*free_func)(void *)) {
    return dl_list_init(NULL, free_func);
}


/*!
 * \brief           Frees memory and releases resources used by a queue.
 * \param que       A pointer to the queue.
 */

void queue_free(queue que) {
    dl_list_free(que);
}


/*!
 * \brief           Gets the number of items in a queue.
 * \param que       A pointer to the queue.
 * \returns         The number of items in the queue.
 */

size_t queue_length(const queue que) {
    return dl_list_length(que);
}


/*!
 * \brief           Checks if a queue is empty.
 * \param que       A pointer to the queue.
 * \returns         `true` is the queue is empty, `false` if not.
 */

bool queue_isempty(const queue que) {
    return dl_list_isempty(que);
}


/*!
 * \brief           Pops a data item from the queue.
 * \details         The item returned was previously allocated using
 * `malloc()`, so the user must `free()` the returned pointer when done.
 * \param que       A pointer to the queue.
 * \returns         A `void` pointer to the popped data item.
 */

void * queue_pop(queue que) {
    dl_list_node popped_node = dl_list_remove_at(que, 0);
    void * data = popped_node->data;
    free(popped_node);
    return data;
}


/*!
 * \brief           Pushes a data item onto the back of the queue.
 * \details         The provided pointer should point to dynamically
 * allocated memory.
 * \param que       A pointer to the queue.
 * \param data      A pointer to the data item to be pushed.
 */

void queue_pushback(queue que, void * data) {
    dl_list_append(que, data);
}
