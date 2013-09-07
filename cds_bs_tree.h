/*!
 * \file            cds_bs_tree.h
 * \brief           User interface to binary search tree data structure.
 * \author          Paul Griffiths
 * \copyright       Copyright 2013 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */


#ifndef PG_CDS_BINARY_SEARCH_TREE_H
#define PG_CDS_BINARY_SEARCH_TREE_H

#include <stddef.h>

/*!
 * \brief           Struct for binary search tree node.
 */

typedef struct bs_tree_node_t {
    void * data;                    /*!< Pointer to data */
    struct bs_tree_node_t * left;   /*!< Pointer to left child node */
    struct bs_tree_node_t * right;  /*!< Pointer to right child node */
} bs_tree_node_t;


/*!
 * \brief           Typedef for tree pointer.
 */

typedef struct bs_tree_t * bs_tree;


/*  Function declarations  */

#ifdef __cplusplus
extern "C" {
#endif

bs_tree bs_tree_init(int (*cfunc)(const void *, const void *));
void bs_tree_free(bs_tree tree);

bool bs_tree_isempty(const bs_tree tree);
size_t bs_tree_length(const bs_tree tree);

bool bs_tree_insert(bs_tree tree, void * data);
bool bs_tree_search(bs_tree tree, void * data);

#ifdef __cplusplus
}
#endif


#endif          /*  PG_CDS_BINARY_SEARCH_TREE_H  */
