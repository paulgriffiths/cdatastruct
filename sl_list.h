/*!
 * \file            sl_list.h
 * \brief           Developer interface to singly linked list data structure.
 * \author          Paul Griffiths
 * \copyright       Copyright 2013 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */


#ifndef PG_CDS_SINGLY_LINKED_LIST_DEV_H
#define PG_CDS_SINGLY_LINKED_LIST_DEV_H

#include <stddef.h>
#include "cds_sl_list.h"


/*!
 * \brief           Struct to contain a list.
 */

typedef struct sl_list_t {
    struct sl_list_node_t * front;      /*!< Pointer to first node */
    size_t length;                      /*!< Length of list */
    int (*cfunc)();                     /*!< Pointer to compare function */
} sl_list_t;


/*!
 * \brief           Typedef for list node.
 */

typedef struct sl_list_node_t * sl_list_node;


/*  Function declarations  */

#ifdef __cplusplus
extern "C" {
#endif

sl_list_node sl_list_new_node(void * data);
void sl_list_free_node(sl_list_node node);

sl_list_node sl_list_remove_at(sl_list list, const size_t index);

void sl_list_find(const sl_list list, const void * data,
                  sl_list_itr * p_itr, int * p_index);

#ifdef __cplusplus
}
#endif


#endif          /*  PG_CDS_SINGLY_LINKED_LIST_DEV_H  */
