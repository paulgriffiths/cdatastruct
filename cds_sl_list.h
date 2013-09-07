/*!
 * \file            cds_sl_list.h
 * \brief           User interface to singly linked list data structure.
 * \author          Paul Griffiths
 * \copyright       Copyright 2013 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */


#ifndef PG_CDS_SINGLY_LINKED_LIST_H
#define PG_CDS_SINGLY_LINKED_LIST_H

#include <stddef.h>

/*!
 * \brief           Struct for singly linked list node.
 */

typedef struct sl_list_node_t {
    void * data;                    /*!< Pointer to data */
    struct sl_list_node_t * next;   /*!< Pointer to next node */
} sl_list_node_t;


/*!
 * \brief           Typedef for list pointer.
 */

typedef struct sl_list_t * sl_list;


/*!
 * \brief           Typedef for list iterator.
 */

typedef struct sl_list_node_t * sl_list_itr;


/*  Function declarations  */

#ifdef __cplusplus
extern "C" {
#endif

sl_list sl_list_init(int (*cfunc)(const void *, const void *),
                     void (*free_func)(void *));
void sl_list_free(sl_list list);

size_t sl_list_length(const sl_list list);
bool sl_list_isempty(const sl_list list);

void sl_list_prepend(sl_list list, void * data);
int sl_list_insert_at(sl_list list, const size_t index, void * data);
int sl_list_insert_after(sl_list list, const sl_list_itr itr, void * data);

int sl_list_delete_at(sl_list list, const size_t index);

int sl_list_find_index(const sl_list list, const void * data);
sl_list_itr sl_list_find_itr(const sl_list list, const void * data);
void * sl_list_data(const sl_list list, const size_t index);

sl_list_itr sl_list_first(const sl_list list);
sl_list_itr sl_list_next(const sl_list_itr itr);
sl_list_itr sl_list_itr_from_index(const sl_list list, const size_t index);

void sl_list_lock(sl_list list);
void sl_list_unlock(sl_list list);

#ifdef __cplusplus
}
#endif


#endif          /*  PG_CDS_SINGLY_LINKED_LIST_H  */
