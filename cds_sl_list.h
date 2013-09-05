/*!
 * \file            sl_list.h
 * \brief           Interface to singly linked list data structure.
 * \details         Interface to singly linked list data structure.
 * \author          Paul Griffiths
 * \copyright       Copyright 2013 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */


#ifndef PG_CDS_SINGLY_LINKED_LIST_H
#define PG_CDS_SINGLY_LINKED_LIST_H

#include <stddef.h>

typedef struct sl_list_node_t {
    void * data;
    struct sl_list_node_t * next;
} sl_list_node_t;

typedef struct sl_list_t {
    struct sl_list_node_t * front;
    size_t length;
} sl_list_t;

typedef struct sl_list_t * sl_list;
typedef struct sl_list_node_t * sl_list_node;
typedef struct sl_list_node_t * sl_list_itr;

sl_list sl_list_init(void);
void sl_list_free(sl_list list);
size_t sl_list_length(sl_list list);
void sl_list_insert_front(sl_list list, void * data);
void sl_list_delete_front(sl_list list);
int sl_list_insert_at(sl_list list, const size_t index, void * data);
sl_list_itr sl_list_first(sl_list list);
sl_list_itr sl_list_next(sl_list_itr itr);

sl_list_node sl_list_remove_front(sl_list list);
sl_list_node sl_list_new_node(void * data);
void sl_list_free_node(sl_list_node node);



#endif          /*  PG_CDS_SINGLY_LINKED_LIST_H  */
