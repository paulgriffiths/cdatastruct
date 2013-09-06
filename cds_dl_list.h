/*!
 * \file            cds_dl_list.h
 * \brief           User interface to doubly linked list data structure.
 * \author          Paul Griffiths
 * \copyright       Copyright 2013 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */


#ifndef PG_CDS_DOUBLY_LINKED_LIST_H
#define PG_CDS_DOUBLY_LINKED_LIST_H

#include <stddef.h>

/*!
 * \brief           Struct for double linked list node.
 */

typedef struct dl_list_node_t {
    void * data;                    /*!< Pointer to data */
    struct dl_list_node_t * next;   /*!< Pointer to next node */
    struct dl_list_node_t * prev;   /*!< Pointer to previous node */
} dl_list_node_t;


/*!
 * \brief           Typedef for list pointer.
 */

typedef struct dl_list_t * dl_list;


/*!
 * \brief           Typedef for list iterator.
 */

typedef struct dl_list_node_t * dl_list_itr;


/*  Function declarations  */

#ifdef __cplusplus
extern "C" {
#endif

dl_list dl_list_init(int (*cfunc)(const void *, const void *));
void dl_list_free(dl_list list);

size_t dl_list_length(const dl_list list);
bool dl_list_isempty(const dl_list list);

void dl_list_prepend(dl_list list, void * data);
void dl_list_append(dl_list list, void * data);
int dl_list_insert_before(dl_list list, const dl_list_itr itr, void * data);
int dl_list_insert_at(dl_list list, const size_t index, void * data);
int dl_list_insert_after(dl_list list, const dl_list_itr itr, void * data);

int dl_list_delete_at(dl_list list, const size_t index);

int dl_list_find_index(const dl_list list, const void * data);
dl_list_itr dl_list_find_itr(const dl_list list, const void * data);
void * dl_list_data(const dl_list list, const size_t index);

dl_list_itr dl_list_first(const dl_list list);
dl_list_itr dl_list_last(const dl_list list);
dl_list_itr dl_list_next(const dl_list_itr itr);
dl_list_itr dl_list_prev(const dl_list_itr itr);
dl_list_itr dl_list_itr_from_index(const dl_list list, const size_t index);

#ifdef __cplusplus
}
#endif

#endif          /*  PG_CDS_DOUBLY_LINKED_LIST_H  */
