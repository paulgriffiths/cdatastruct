/*!
 * \file            bs_tree.c
 * \brief           Implementation of binary search tree data structure.
 * \author          Paul Griffiths
 * \copyright       Copyright 2013 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */


#include <stdlib.h>
#include <stdbool.h>
#include <paulgrif/chelpers.h>
#include "cds_common.h"
#include "bs_tree.h"

/*!
 * \brief           Initializes a new binary search tree.
 * \param cfunc     A pointer to a compare function. The function should
 * return `int` and accept two parameters of type `void *`. It should
 * return less than 1 if the first parameter is less than the second,
 * greater than 1 if the first parameter is greater than the second,
 * and zero if the parameters are equal.
 * \returns         A pointer to the new tree.
 */

bs_tree bs_tree_init(int (*cfunc)(const void *, const void *)) {
    bs_tree new_tree = term_malloc(sizeof(*new_tree));
    new_tree->root = NULL;
    new_tree->length = 0;
    new_tree->cfunc = cfunc;
    return new_tree;
}


/*!
 * \brief           Frees the resources associated with a tree.
 * \param tree      A pointer to the tree to free.
 */

void bs_tree_free(bs_tree tree) {
    bs_tree_free_subtree(tree->root);
    free(tree);
}


/*!
 * \brief           Returns the number of elements in a tree.
 * \param tree      A pointer to the tree.
 * \returns         The number of elements in the tree.
 */

size_t bs_tree_length(const bs_tree tree) {
    return tree->length;
}


/*!
 * \brief           Checks if a tree is empty.
 * \param tree      A pointer to the tree.
 * \returns         `true` if the tree is empty, otherwise `false`.
 */

bool bs_tree_isempty(const bs_tree tree) {
    return ( tree->root ) ? false : true;
}


/*!
 * \brief           Frees the resources associated with a subtree.
 * \details         This function frees the node recursively.
 * \param node      A pointer to the tree node at the root of the subtree.
 */

void bs_tree_free_subtree(bs_tree_node node) {
    if ( node ) {
        free(node->data);
        bs_tree_free_subtree(node->left);
        bs_tree_free_subtree(node->right);
        free(node);
    }
}


/*!
 * \brief           Searches a tree for a piece of data.
 * \param tree      A pointer to the tree.
 * \param data      The data for which to search.
 * \returns         `true` is the data is found, `false` otherwise.
 */

bool bs_tree_search(bs_tree tree, void * data) {
    bool found = bs_tree_search_subtree(tree, tree->root, data);
    return found;
}


/*!
 * \brief           Inserts data into a tree.
 * \param tree      A pointer to the tree.
 * \param data      The data to insert.
 * \returns         `true` if the data was succesfully inserted, `false`
 * if that data was already present in the tree.
 */

bool bs_tree_insert(bs_tree tree, void * data) {
    return bs_tree_insert_subtree(tree, &tree->root, data);
}


/*!
 * \brief           Searches a subtree for a piece of data.
 * \param tree      A pointer to the tree.
 * \param node      A pointer to the node at the root of the subtree.
 * \param data      A pointer to the data for which to search.
 * \returns         A pointer to the node in which the data was found,
 * or `NULL` if the data was not found.
 */

bs_tree_node bs_tree_search_subtree(bs_tree tree,
        bs_tree_node node, void * data) {
    bs_tree_node searchnode = node;
    bool found = false;
    int compare;

    while ( !found && searchnode ) {
        compare = tree->cfunc(data, searchnode->data);
        if ( !compare ) {
            found = true;
        } else if ( compare < 0 ) {
            searchnode = searchnode->left;
        } else {
            searchnode = searchnode->right;
        }
    }

    return searchnode;
}


/*!
 * \brief           Inserts a data element into a subtree.
 * \param tree      A pointer to the tree
 * \param p_node    A pointer to the pointer to the node at the root of the
 * subtree.
 * \param data      A pointer to the data to which to insert.
 * \returns         `true` if the data was successfully inserted, `false`
 * if the data was already present in the subtree.
 */

bool bs_tree_insert_subtree(bs_tree tree, bs_tree_node * p_node, void * data) {
    bs_tree_node last_node = bst_insert_search(tree, *p_node, data);
    bs_tree_node new_node;
    bool inserted = false;

    if ( last_node || !(*p_node) ) {
        new_node = term_malloc(sizeof(*new_node));
        new_node->data = data;
        new_node->left = NULL;
        new_node->right = NULL;

        if ( *p_node ) {
            int compare = tree->cfunc(data, last_node->data);
            if ( compare < 0 ) {
                last_node->left = new_node;
            } else {
                last_node->right = new_node;
            }
        } else {
            *p_node = new_node;
        }

        ++tree->length;
        inserted = true;
    }

    return inserted;
}


/*!
 * \brief       Searches a tree for insertion purposes.
 * \details     The function searches the tree for a piece of data,
 * and if it is not found, returns a pointer to the node under which
 * it should be inserted.
 * \param tree  A pointer to the tree.
 * \param node  A pointer to the node at the root of the tree.
 * \param data  A pointer to the data for which to search.
 * \returns     `NULL` if the data was found and is already in the tree,
 * or a pointer to the last node tried if the data is not present.
 */

bs_tree_node bst_insert_search(bs_tree tree, bs_tree_node node, void * data) {
    bs_tree_node searchnode = node;
    bs_tree_node last_try = node;
    bool found = false;
    int compare;

    if ( !searchnode ) {
        return NULL;
    }

    while ( !found && searchnode ) {
        compare = tree->cfunc(data, searchnode->data);
        if ( !compare ) {
            found = true;
        } else if ( compare < 0 ) {
            last_try = searchnode;
            searchnode = searchnode->left;
        } else {
            last_try = searchnode;
            searchnode = searchnode->right;
        }
    }

    return found ? NULL : last_try;
}
