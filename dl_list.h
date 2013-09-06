/*!
 * \file            dl_list.h
 * \brief           Developer interface to double linked list data structure.
 * \author          Paul Griffiths
 * \copyright       Copyright 2013 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */


#ifndef PG_CDS_DOUBLY_LINKED_LIST_DEV_H
#define PG_CDS_DOUBLY_LINKED_LIST_DEV_H

#include <stddef.h>
#include "cds_dl_list.h"


/*!
 * \brief           Struct to contain a list.
 */

typedef struct dl_list_t {
    struct dl_list_node_t * front;      /*!< Pointer to first node */
    struct dl_list_node_t * back;       /*!< Pointer to last node */
    size_t length;                      /*!< Length of list */
    int (*cfunc)();                     /*!< Pointer to compare function */
} dl_list_t;


/*!
 * \brief           Typedef for list node.
 */

typedef struct dl_list_node_t * dl_list_node;


/*  Function declarations  */

#ifdef __cplusplus
extern "C" {
#endif

dl_list_node dl_list_remove_at(dl_list list, const size_t index);
dl_list_node dl_list_new_node(void * data);
void dl_list_free_node(dl_list_node node);

#ifdef __cplusplus
}
#endif

#endif          /*  PG_CDS_DOUBLY_LINKED_LIST_DEV_H  */