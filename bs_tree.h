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


#ifdef CDS_THREAD_SUPPORT

  /*!
   * \brief         Enable POSIX library.
   */

  #define _POSIX_C_SOURCE 200809L
  #include <pthread.h>
#endif


/*!
 * \brief           Struct to contain a binary search tree.
 */

typedef struct bs_tree_t {
#ifdef CDS_THREAD_SUPPORT
    pthread_mutex_t mutex;              /*!< Mutex */
#endif
    struct bs_tree_node_t * root;       /*!< Pointer to root node */
    size_t length;                      /*!< Length of list */
    int (*cfunc)();                     /*!< Pointer to compare function */
    void (*free_func)();                /*!< Pointer to node free function */
} sl_list_t;


/*!
 * \brief           Typedef for binary search tree node.
 */

typedef struct bs_tree_node_t * bs_tree_node;


/*  Function declarations  */

#ifdef __cplusplus
extern "C" {
#endif

bs_tree_node bs_tree_new_node(void * data);
void bs_tree_free_subtree(bs_tree tree, bs_tree_node node);
bs_tree_node bs_tree_search_node(const bs_tree tree, const void * key);
bool bs_tree_insert_subtree(bs_tree tree, bs_tree_node * p_node, void * data);
bs_tree_node bs_tree_insert_search(bs_tree tree, void * key, bool * found);

void bs_tree_preorder_left_traverse_int(bs_tree tree, bs_tree_node node,
        void (*dfunc)(void *, void *), void * arg);
void bs_tree_inorder_left_traverse_int(bs_tree tree, bs_tree_node node,
        void (*dfunc)(void *, void *), void * arg);
void bs_tree_postorder_left_traverse_int(bs_tree tree, bs_tree_node node,
        void (*dfunc)(void *, void *), void * arg);
void bs_tree_preorder_right_traverse_int(bs_tree tree, bs_tree_node node,
        void (*dfunc)(void *, void *), void * arg);
void bs_tree_inorder_right_traverse_int(bs_tree tree, bs_tree_node node,
        void (*dfunc)(void *, void *), void * arg);
void bs_tree_postorder_right_traverse_int(bs_tree tree, bs_tree_node node,
        void (*dfunc)(void *, void *), void * arg);

#ifdef __cplusplus
}
#endif


#endif          /*  PG_CDS_BINARY_SEARCH_TREE_DEV_H  */
