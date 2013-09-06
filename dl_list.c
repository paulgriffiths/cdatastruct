/*!
 * \file            dl_list.c
 * \brief           Implementation of doubly linked list data structure.
 * \author          Paul Griffiths
 * \copyright       Copyright 2013 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */


#include <stdlib.h>
#include <stdbool.h>
#include <paulgrif/chelpers.h>
#include "cds_common.h"
#include "dl_list.h"

/*!
 * \brief           Initializes a new doubly linked list.
 * \param cfunc     A pointer to a compare function. The function should
 * return `int` and accept two parameters of type `void *`. It should
 * return less than 1 if the first parameter is less than the second,
 * greater than 1 if the first parameter is greater than the second,
 * and zero if the parameters are equal.
 * \returns         A pointer to the new list.
 */

dl_list dl_list_init(int (*cfunc)(const void *, const void *)) {
    dl_list new_list = term_malloc(sizeof(*new_list));

    new_list->front = NULL;
    new_list->back = NULL;
    new_list->length = 0;
    new_list->cfunc = cfunc;

    return new_list;
}


/*!
 * \brief           Frees the resources associated with a list.
 * \param list      A pointer to the list to free.
 */

void dl_list_free(dl_list list) {
    while ( dl_list_isempty(list) != true ) {
        dl_list_delete_at(list, 0);
    }
    free(list);
}


/*!
 * \brief           Returns the number of elements in a list.
 * \param list      A pointer to the list.
 */

size_t dl_list_length(const dl_list list) {
    return list->length;
}


/*!
 * \brief           Checks if a list is empty.
 * \param list      A pointer to the list.
 * \returns         `true` if the list is empty, otherwise `false`.
 */

bool dl_list_isempty(const dl_list list) {
    return (list->front) ? false : true;
}


/*!
 * \brief           Inserts an element at the beginning of a list.
 * \param list      A pointer to the list.
 * \param data      A pointer to the data to add. The memory pointed
 * to by this parameter must be dynamically allocated, as an attempt
 * will be made to `free()` it when deleting the list.
 */

void dl_list_prepend(dl_list list, void * data) {
    dl_list_insert_at(list, 0, data);
}


/*!
 * \brief           Inserts an element at the end of a list.
 * \param list      A pointer to the list.
 * \param data      A pointer to the data to add. The memory pointed
 * to by this parameter must be dynamically allocated, as an attempt
 * will be made to `free()` it when deleting the list.
 */

void dl_list_append(dl_list list, void * data) {
    if ( dl_list_isempty(list) ) {
        dl_list_insert_at(list, 0, data);
    } else {
        dl_list_insert_after(list, list->back, data);
    }
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

int dl_list_insert_at(dl_list list, const size_t index, void * data) {
    if ( index > list->length ) {
        return CDSERR_OUTOFRANGE;
    }

    dl_list_node new_node = dl_list_new_node(data);

    if ( index == 0 ) {
        dl_list_insert_node_front(list, new_node);
    } else if ( index == list->length ) {
        dl_list_insert_node_back(list, new_node);
    } else {
        dl_list_node after = dl_list_index(list, index);
        dl_list_insert_node_before_mid(list, after, new_node);
    }

    return 0;
}


/*!
 * \brief           Inserts an element after a provided iterator.
 * \details         Note that dl_list_first() may return a NULL iterator
 * when the list is empty. One reasonable behavior for this function would
 * be to add a new node to the list in that case. However, an iterator
 * may also become NULL when advanced to the end of the list. One possible
 * way to modify this function would be to check the length of this list
 * when the iterator is NULL, and if it is zero, add the first node to
 * the list. However, the semantic meaning of adding an element *after*
 * an iterator breaks down if that that iterator does not point to an
 * existing element. Therefore, it is simpler for this function to simply
 * refuse to handle NULL iterators. It is unlikely a user would want to
 * call this function unless there are already elements in a list, and
 * a valid iterator has been returned, e.g. through a find function.
 * \param list      A pointer to the list.
 * \param itr       The iterator after which to insert.
 * \param data      A pointer to the data to add. The memory pointed
 * to by this parameter must be dynamically allocated, as an attempt
 * will be made to `free()` it when deleting the list.
 * \returns         0 on success, CDSERR_BADITERATOR if `itr` is a
 * NULL pointer.
 */

int dl_list_insert_after(dl_list list, const dl_list_itr itr, void * data) {
    if ( itr == NULL ) {
        return CDSERR_BADITERATOR;
    }

    dl_list_node new_node = dl_list_new_node(data);
    if ( itr->next ) {
        dl_list_insert_node_after_mid(list, itr, new_node);
    } else {
        dl_list_insert_node_back(list, new_node);
    }

    return 0;
}


/*!
 * \brief           Inserts an element before a provided iterator.
 * \param list      A pointer to the list.
 * \param itr       The iterator after which to insert.
 * \param data      A pointer to the data to add. The memory pointed
 * to by this parameter must be dynamically allocated, as an attempt
 * will be made to `free()` it when deleting the list.
 * \returns         0 on success, CDSERR_BADITERATOR if `itr` is a
 * NULL pointer.
 */

int dl_list_insert_before(dl_list list, const dl_list_itr itr, void * data) {
    if ( itr == NULL ) {
        return CDSERR_BADITERATOR;
    }

    dl_list_node new_node = dl_list_new_node(data);
    if ( itr->prev ) {
        dl_list_insert_node_before_mid(list, itr, new_node);
    } else {
        dl_list_insert_node_front(list, new_node);
    }

    return 0;
}


/*!
 * \brief           Finds the index of the specified data in a list.
 * \param list      A pointer to the list.
 * \param data      A pointer to the data to find.
 * \returns         The index of the element, if found, or CDSERR_NOTFOUND
 * if it is not in the list.
 */

int dl_list_find_index(const dl_list list, const void * data) {
    dl_list_node node = list->front;
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

    return found ? index : CDSERR_NOTFOUND;
}


/*!
 * \brief           Gets an iterator to the specified data in a list.
 * \param list      A pointer to the list.
 * \param data      A pointer to the data to find.
 * \returns         An iterator to the found element, or NULL is the
 * element is not in the list.
 */

dl_list_itr dl_list_find_itr(const dl_list list, const void * data) {
    dl_list_itr itr = list->front;
    int index = 0;
    bool found = false;

    while ( itr && !found ) {
        if ( list->cfunc(itr->data, data) == 0 ) {
            found = true;
        } else {
            itr = itr->next;
            ++index;
        }
    }

    return itr;
}


/*!
 * \brief           Returns a pointer to the data at a specified index.
 * \param list      A pointer to the list.
 * \param index     The index of the data.
 * \returns         A pointer to the data, or NULL if the index is out
 * of range.
 */

void * dl_list_data(const dl_list list, const size_t index) {
    dl_list_itr itr = dl_list_index(list, index);
    return itr ? itr->data : NULL;
}


/*!
 * \brief           Returns an iterator to the first element of a list.
 * \param list      A pointer to the list.
 * \returns         An iterator to the first element.
 */

dl_list_itr dl_list_first(const dl_list list) {
    return list->front;
}


/*!
 * \brief           Returns an iterator to the last element of a list.
 * \param list      A pointer to the list.
 * \returns         An iterator to the first element.
 */

dl_list_itr dl_list_last(const dl_list list) {
    return list->back;
}


/*!
 * \brief           Advances a list iterator by one element.
 * \param itr       The iterator to advance
 * \returns         The advanced iterator.
 */

dl_list_itr dl_list_next(const dl_list_itr itr) {
    return itr->next;
}


/*!
 * \brief           Backs up a list iterator by one element.
 * \param itr       The iterator to back up.
 * \returns         The backed up iterator.
 */

dl_list_itr dl_list_prev(const dl_list_itr itr) {
    return itr->prev;
}


/*!
 * \brief           Return an iterator to a specified element of a list.
 * \param list      A pointer to the list.
 * \param index     The specified index.
 * \returns         The iterator, or NULL if `index` is out of range.
 */

dl_list_itr dl_list_index(const dl_list list, const size_t index) {
    if ( index >= list->length ) {
        return NULL;
    }

    dl_list_itr element;

    if ( index == 0 ) {
        element = list->front;
    } else if ( index == list->length - 1 ) {
        element = list->back;
    } else {

        if ( index <= list->length / 2 ) {

            /*  Find indexed element from front  */

            size_t i = index;
            element = list->front->next;

            while ( --i ) {
                element = element->next;
            }
        } else {

            /*  Find indexed element from back  */

            size_t i = list->length - 1;
            element = list->back->prev;

            while ( --i > index ) {
                element = element->prev;
            }
        }
    }

    return element;
}


/*!
 * \brief           Deletes a list element at a specified index.
 * \param list      A pointer to the list.
 * \param index     The index of the element to delete.
 * \returns         0 on success, CDSERR_OUTOFRANGE if the the index
 * is out of range.
 */

int dl_list_delete_at(dl_list list, const size_t index) {
    dl_list_node rm_node = dl_list_remove_at(list, index);

    if ( rm_node == NULL ) {
        return CDSERR_OUTOFRANGE;
    }

    dl_list_free_node(rm_node);
    return 0;
}


/*!
 * \brief           Removes, but does not delete, an element at an index.
 * \param list      A pointer to the list.
 * \param index     The index of the element to be removed.
 * \returns         A pointer to the removed node. This should be
 * `free()`d by calling dl_list_free_node().
 */

dl_list_node dl_list_remove_at(dl_list list, const size_t index) {
    if ( index >= list->length ) {
        return NULL;
    }

    dl_list_node itr = list->front;
    if ( index == 0 ) {
        dl_list_node new_front = itr->next;
        list->front = new_front;
        if ( new_front ) {
            new_front->prev = NULL;
        } else {
            list->back = new_front;
        }
        list->front = new_front;
    } else {
        size_t i = index;
        dl_list_node before = itr;
        itr = itr->next;

        while ( --i ) {
            before = itr;
            itr = itr->next;
        }

        dl_list_node after = itr->next;
        before->next = after;
        if ( after ) {
            after->prev = before;
        } else {
            list->back = before;
        }
    }

    itr->next = NULL;
    itr->prev = NULL;
    --list->length;

    return itr;
}


/*!
 * \brief           Inserts a node at the front of a list.
 * \param list      A pointer to the list.
 * \param node      A pointer to the node to insert.
 */

void dl_list_insert_node_front(dl_list list, dl_list_node node) {
    if ( dl_list_isempty(list) ) {
        list->front = list->back = node;
    } else {
        dl_list_node old_front = list->front;
        list->front = node;
        node->prev = NULL;
        node->next = old_front;
        old_front->prev = node;
    }
    ++list->length;
}


/*!
 * \brief           Inserts a node at the back of a list.
 * \param list      A pointer to the list.
 * \param node      A pointer to the node to insert.
 */

void dl_list_insert_node_back(dl_list list, dl_list_node node) {
    if ( dl_list_isempty(list) ) {
        list->front = list->back = node;
    } else {
        dl_list_node old_back = list->back;
        list->back = node;
        node->prev = old_back;
        node->next = NULL;
        old_back->next = node;
    }
    ++list->length;
}


/*!
 * \brief           Inserts a node in the middle of a list before a specified
 * iterator.
 * \param list      A pointer to the list.
 * \param itr       The iterator before which to insert. As this is
 * inserting in the middle, this iterator should not be either the front
 * or the back of the list, i.e. both the `prev` and `next` members
 * should be non-NULL.
 * \param node      A pointer to the node to insert.
 */

void dl_list_insert_node_before_mid(dl_list list,
        dl_list_itr itr, dl_list_node node) {
    dl_list_node before = itr->prev;
    dl_list_node after = itr;
    node->prev = before;
    node->next = after;
    before->next = node;
    after->prev = node;
    ++list->length;
}


/*!
 * \brief           Inserts a node in the middle of a list after a specified
 * iterator.
 * \param list      A pointer to the list.
 * \param itr       The iterator after which to insert. As this is
 * inserting in the middle, this iterator should not be either the front
 * or the back of the list, i.e. both the `prev` and `next` members
 * should be non-NULL.
 * \param node      A pointer to the node to insert.
 */

void dl_list_insert_node_after_mid(dl_list list,
        dl_list_itr itr, dl_list_node node) {
    dl_list_node before = itr;
    dl_list_node after = itr->next;
    node->prev = before;
    node->next = after;
    before->next = node;
    after->prev = node;
    ++list->length;
}


/*!
 * \brief           Creates a new list node.
 * \param data      The data for the new node.
 * \returns         A pointer to the newly created node.
 */

dl_list_node dl_list_new_node(void * data) {
    dl_list_node new_node = term_malloc(sizeof(*new_node));
    new_node->data = data;
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}


/*!
 * \brief           Frees resources for a node and any data.
 * \param node      A pointer to the node to free.
 */

void dl_list_free_node(dl_list_node node) {
    free(node->data);
    free(node);
}
