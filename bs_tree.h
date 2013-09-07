/*!
 * \file            bs_tree.h
 * \brief           Developer interface to binary search tree data structure.
 * \author          Paul Griffiths
 * \copyright       Copyright 2013 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */


#ifndef PG_CDS_BINARY_SEARCH_TREE_DEV_H
#define PG_CDS_BINARY_SEARCH_TREE_DEV_H

#include <stddef.h>
#include "cds_bs_tree.h"


/*!
 * \brief           Struct to contain a binary search tree.
 */

typedef struct bs_tree_t {
    struct bs_tree_node_t * root;       /*!< Pointer to root node */
    size_t length;                      /*!< Length of list */
    int (*cfunc)();                     /*!< Pointer to compare function */
} sl_list_t;


/*!
 * \brief           Typedef for binary search tree node.
 */

typedef struct bs_tree_node_t * bs_tree_node;


/*  Function declarations  */

#ifdef __cplusplus
extern "C" {
#endif

void bs_tree_free_subtree(bs_tree_node node);
bs_tree_node bs_tree_search_subtree(bs_tree tree,
        bs_tree_node node, void * key);
bool bs_tree_insert_subtree(bs_tree tree, bs_tree_node * p_node, void * data);
bs_tree_node bst_insert_search(bs_tree tree, bs_tree_node node, void * key);

#ifdef __cplusplus
}
#endif


#endif          /*  PG_CDS_BINARY_SEARCH_TREE_DEV_H  */
