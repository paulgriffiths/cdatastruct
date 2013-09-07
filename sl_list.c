/*!
 * \file            sl_list.c
 * \brief           Implementation of singly linked list data structure.
 * \author          Paul Griffiths
 * \copyright       Copyright 2013 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */


#include <stdlib.h>
#include <stdbool.h>
#include <paulgrif/chelpers.h>
#include "cds_common.h"
#include "sl_list.h"

/*!
 * \brief           Initializes a new singly linked list.
 * \param cfunc     A pointer to a compare function. The function should
 * return `int` and accept two parameters of type `void *`. It should
 * return less than 1 if the first parameter is less than the second,
 * greater than 1 if the first parameter is greater than the second,
 * and zero if the parameters are equal.
 * \returns         A pointer to the new list.
 */

sl_list sl_list_init(int (*cfunc)(const void *, const void *)) {
    sl_list new_list = term_malloc(sizeof(*new_list));
    new_list->front = NULL;
    new_list->length = 0;
    new_list->cfunc = cfunc;
    return new_list;
}


/*!
 * \brief           Frees the resources associated with a list.
 * \param list      A pointer to the list to free.
 */

void sl_list_free(sl_list list) {
    while ( list->front ) {
        sl_list_delete_at(list, 0);
    }
    free(list);
}


/*!
 * \brief           Returns the number of elements in a list.
 * \param list      A pointer to the list.
 */

size_t sl_list_length(const sl_list list) {
    return list->length;
}


/*!
 * \brief           Checks if a list is empty.
 * \param list      A pointer to the list.
 * \returns         `true` if the list is empty, otherwise `false`.
 */

bool sl_list_isempty(const sl_list list) {
    return ( list->front ) ? false : true;
}


/*!
 * \brief           Inserts an element at the beginning of a list.
 * \param list      A pointer to the list.
 * \param data      A pointer to the data to add. The memory pointed
 * to by this parameter must be dynamically allocated, as an attempt
 * will be made to `free()` it when deleting the list.
 */

void sl_list_prepend(sl_list list, void * data) {
    sl_list_insert_at(list, 0, data);
}


/*!
 * \brief           Inserts an element at the specified index of a list.
 * \param list      A pointer to the list.
 * \param index     The index at which to insert. Setting this equal
 * to the length of the list (i.e. to one element past the zero-based
 * index of the last element) inserts the element at the end of the list.
 * \param data      A pointer to the data to add. The memory pointed
 * to by this parameter must be dynamically allocated, as an attempt
 * will be made to `free()` it when deleting the list.
 * \returns         0 on success, CDSERR_OUTOFRANGE if `index` exceeds
 * the length of the list.
 */

int sl_list_insert_at(sl_list list, const size_t index, void * data) {
    if ( index > list->length ) {
        return CDSERR_OUTOFRANGE;
    }

    if ( index == 0 ) {
        sl_list_node new_node = sl_list_new_node(data);
        new_node->next = list->front;
        list->front = new_node;
        ++list->length;
    } else {
        size_t i = index;
        sl_list_node before = list->front;

        while ( --i ) {
            before = before->next;
        }

        sl_list_insert_after(list, before, data);
    }
    
    return 0;
}


/*!
 * \brief           Inserts an element after a provided iterator.
 * \param list      A pointer to the list.
 * \param itr       The iterator after which to insert.
 * \param data      A pointer to the data to add. The memory pointed
 * to by this parameter must be dynamically allocated, as an attempt
 * will be made to `free()` it when deleting the list.
 * \returns         0 on success, CDSERR_BADITERATOR if `itr` is a
 * NULL pointer.
 */

int sl_list_insert_after(sl_list list, const sl_list_itr itr, void * data) {
    if ( itr == NULL ) {
        return CDSERR_BADITERATOR;
    }

    sl_list_node new_node = sl_list_new_node(data);
    new_node->next = itr->next;
    itr->next = new_node;
    ++list->length;

    return 0;
}


/*!
 * \brief           Deletes a list element at a specified index.
 * \param list      A pointer to the list.
 * \param index     The index of the element to delete.
 * \returns         0 on success, CDSERR_OUTOFRANGE if the the index
 * is out of range.
 */

int sl_list_delete_at(sl_list list, const size_t index) {
    sl_list_node rm_node = sl_list_remove_at(list, index);

    if ( rm_node == NULL ) {
        return CDSERR_OUTOFRANGE;
    }

    sl_list_free_node(rm_node);
    return 0;
}


/*!
 * \brief           Gets an index to the specified data in a list.
 * \param list      A pointer to the list.
 * \param data      A pointer to the data to find.
 * \returns         The index of the found element, or CDSERR_NOTFOUND
 * if the element is not in the list.
 */

int sl_list_find_index(const sl_list list, const void * data) {
    int index;
    sl_list_find(list, data, NULL, &index);
    return index;
}


/*!
 * \brief           Gets an iterator to the specified data in a list.
 * \param list      A pointer to the list.
 * \param data      A pointer to the data to find.
 * \returns         An iterator to the found element, or NULL is the
 * element is not in the list.
 */

sl_list_itr sl_list_find_itr(const sl_list list, const void * data) {
    sl_list_itr itr;
    sl_list_find(list, data, &itr, NULL);
    return itr;
}


/*!
 * \brief           Returns a pointer to the data at a specified index.
 * \param list      A pointer to the list.
 * \param index     The index of the data.
 * \returns         A pointer to the data, or NULL if the index is out
 * of range.
 */

void * sl_list_data(const sl_list list, const size_t index) {
    sl_list_itr itr = sl_list_itr_from_index(list, index);
    return itr ? itr->data : NULL;
}


/*!
 * \brief           Returns an iterator to the first element of a list.
 * \param list      A pointer to the list.
 * \returns         An iterator to the first element.
 */

sl_list_itr sl_list_first(const sl_list list) {
    return list->front;
}


/*!
 * \brief           Advances a list iterator by one element.
 * \param itr       The iterator to advance
 * \returns         The advanced iterator.
 */

sl_list_itr sl_list_next(const sl_list_itr itr) {
    return itr->next;
}


/*!
 * \brief           Return an iterator to a specified element of a list.
 * \param list      A pointer to the list.
 * \param index     The specified index.
 * \returns         The iterator, or NULL if `index` is out of range.
 */

sl_list_itr sl_list_itr_from_index(const sl_list list, const size_t index) {
    if ( index >= list->length ) {
        return NULL;
    }

    sl_list_itr itr = list->front;
    size_t i = index;

    while ( i-- ) {
        itr = itr->next;
    }

    return itr;
}


/*!
 * \brief           Creates a new list node.
 * \param data      The data for the new node.
 * \returns         A pointer to the newly created node.
 */

sl_list_node sl_list_new_node(void * data) {
    sl_list_node new_node = term_malloc(sizeof(*new_node));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}


/*!
 * \brief           Frees resources for a node and any data.
 * \param node      A pointer to the node to free.
 */

void sl_list_free_node(sl_list_node node) {
    free(node->data);
    free(node);
}


/*!
 * \brief           Removes, but does not delete, an element at an index.
 * \param list      A pointer to the list.
 * \param index     The index of the element to be removed.
 * \returns         A pointer to the removed node. This should be
 * `free()`d by calling sl_list_free_node().
 */

sl_list_node sl_list_remove_at(sl_list list, const size_t index) {
    if ( index >= list->length ) {
        return NULL;
    }

    sl_list_node itr = list->front;
    if ( index == 0 ) {
        list->front = itr->next;
    } else {
        sl_list_itr before = sl_list_itr_from_index(list, index - 1);
        itr = before->next;
        before->next = itr->next;
    }

    itr->next = NULL;
    --list->length;

    return itr;
}


/*!
 * \brief           Gets an index and iterator to a specified piece of data.
 * \param list      A pointer to the list.
 * \param data      A pointer to the data to find.
 * \param p_itr     A pointer to an iterator to populate with the result.
 * This parameter is ignored if set to NULL.
 * \param p_index   A pointer to an integer index to populate with the result.
 * This parameter is ignored if set to NULL.
 */

void sl_list_find(const sl_list list, const void * data,
                  sl_list_itr * p_itr, int * p_index) {
    sl_list_node node = list->front;
    int index = 0;
    bool found = false;

    while ( node && !found ) {
        if ( list->cfunc(node->data, data) == 0 ) {
            found = true;
        } else {
            node = node->next;
            ++index;
        }
    }

    if ( p_itr ) {
        *p_itr = node;
    }

    if ( p_index ) {
        *p_index = found ? index : CDSERR_NOTFOUND;
    }
}
