/*!
 * \file            sl_list.c
 * \brief           Implementation of singly linked list data structure.
 * \details         Implementation of singly linked list data structure.
 * \author          Paul Griffiths
 * \copyright       Copyright 2013 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */


#include <stdlib.h>
#include <paulgrif/chelpers.h>
#include "cds_common.h"
#include "cds_sl_list.h"

sl_list sl_list_init(void) {
    sl_list new_list = term_malloc(sizeof(*new_list));
    new_list->front = NULL;
    new_list->length = 0;
    return new_list;
}

void sl_list_free(sl_list list) {
    while ( list->front ) {
        sl_list_delete_front(list);
    }
    free(list);
}

size_t sl_list_length(sl_list list) {
    return list->length;
}

void sl_list_insert_front(sl_list list, void * data) {
    sl_list_node new_node = sl_list_new_node(data);
    new_node->next = list->front;
    list->front = new_node;
    ++list->length;
}

void sl_list_delete_front(sl_list list) {
    sl_list_free_node(sl_list_remove_front(list));
}

int sl_list_insert_at(sl_list list, const size_t index, void * data) {
    if ( index > list->length ) {
        return CDSERR_OUTOFRANGE;
    }

    sl_list_node new_node = sl_list_new_node(data);

    if ( index == 0 ) {
        new_node->next = list->front;
        list->front = new_node;
    } else {
        size_t i = index;
        sl_list_node before = list->front;
        sl_list_node after = before->next;

        while ( --i ) {
            before = after;
            after = after->next;
        }

        new_node->next = after;
        before->next = new_node;
    }
    
    ++list->length;

    return 0;
}

sl_list_itr sl_list_first(sl_list list) {
    return list->front;
}

sl_list_itr sl_list_next(sl_list_itr itr) {
    return itr->next;
}

sl_list_node sl_list_remove_front(sl_list list) {
    sl_list_node removed_node = NULL;

    if ( list->front ) {
        removed_node = list->front;
        list->front = removed_node->next;
        --list->length;
    }

    return removed_node;
}

sl_list_node sl_list_new_node(void * data) {
    sl_list_node new_node = term_malloc(sizeof(*new_node));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void sl_list_free_node(sl_list_node node) {
    free(node->data);
    free(node);
}
