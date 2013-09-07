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
 * \param free_func A pointer to a free function. The function should
 * return no value, and accept one parameter of type `void *`. If set
 * to NULL, the standard C `free()` function is used. This function
 * is useful when the data elements are structs which themselves
 * contain dynamically allocated members, which need to be `free()`d
 * before the overall struct is `free()`.
 * \returns         A pointer to the new tree.
 */

bs_tree bs_tree_init(int (*cfunc)(const void *, const void *),
                     void (*free_func)(void *)) {
    bs_tree new_tree = term_malloc(sizeof(*new_tree));
    new_tree->root = NULL;
    new_tree->length = 0;
    new_tree->cfunc = cfunc;
    if ( free_func ) {
        new_tree->free_func = free_func;
    } else {
        new_tree->free_func = free;
    }
    return new_tree;
}


/*!
 * \brief           Frees the resources associated with a tree.
 * \param tree      A pointer to the tree to free.
 */

void bs_tree_free(bs_tree tree) {
    bs_tree_free_subtree(tree, tree->root);
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
 * \brief           Searches a tree for a piece of data.
 * \param tree      A pointer to the tree.
 * \param data      The data for which to search.
 * \returns         `true` is the data is found, `false` otherwise.
 */

bool bs_tree_search(bs_tree tree, void * data) {
    bs_tree_node node = bs_tree_search_node(tree, data);
    return node ? true : false;
}


/*!
 * \brief           Inserts data into a tree.
 * \details         No duplicates are allowed in a binary search tree,
 * so data will only be inserted in the data is not already found in
 * the tree. Since `data` points to dynamically allocated memory, the
 * caller should check the return from this function, and if it returns
 * `false`, it should probably `free()` the data which was not inserted.
 * \param tree      A pointer to the tree.
 * \param data      The data to insert.
 * \returns         `true` if the data was succesfully inserted, `false`
 * if that data was already present in the tree.
 */

bool bs_tree_insert(bs_tree tree, void * data) {
    return bs_tree_insert_subtree(tree, &tree->root, data);
}


/*!
 * \brief           Creates and allocates memory for a new node.
 * \param data      The data for the new node.
 * \returns         A pointer to the newly-created node.
 */

bs_tree_node bs_tree_new_node(void * data) {
    bs_tree_node new_node = term_malloc(sizeof(*new_node));
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}


/*!
 * \brief           Frees the resources associated with a subtree.
 * \details         This function frees the node recursively.
 * \param tree      A pointer to the tree.
 * \param node      A pointer to the tree node at the root of the subtree.
 */

void bs_tree_free_subtree(bs_tree tree, bs_tree_node node) {
    if ( node ) {
        tree->free_func(node->data);
        bs_tree_free_subtree(tree, node->left);
        bs_tree_free_subtree(tree, node->right);
        free(node);
    }
}


/*!
 * \brief           Searches a tree for a piece of data.
 * \param tree      A pointer to the tree.
 * \param data      A pointer to the data for which to search.
 * \returns         A pointer to the node in which the data was found,
 * or `NULL` if the data was not found.
 */

bs_tree_node bs_tree_search_node(bs_tree tree, void * data) {
    bs_tree_node searchnode = tree->root;
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
 * \details         The data element is only inserted if it does not
 * already exist in the tree, i.e. no duplicates are allowed.
 * \param tree      A pointer to the tree
 * \param p_node    A pointer to the pointer to the node at the root of the
 * subtree.
 * \param data      A pointer to the data to which to insert.
 * \returns         `true` if the data was successfully inserted, `false`
 * if the data was already present in the subtree.
 */

bool bs_tree_insert_subtree(bs_tree tree, bs_tree_node * p_node, void * data) {
    bs_tree_node last_node = bst_insert_search(tree, data);
    bool inserted = false;

    /*
     *  Insert only if:
     *   - `last_node` is not `NULL`. If it is, bst_insert_search()
     *     found the data already in the tree; or
     *   - `*p_node` is `NULL`, in which case the tree is empty and
     *     the data obviously is not in the tree.
     */

    if ( last_node || !(*p_node) ) {
        bs_tree_node new_node = bs_tree_new_node(data);
        inserted = true;
        ++tree->length;

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
    }

    return inserted;
}


/*!
 * \brief       Searches a tree for insertion purposes.
 * \details     The function searches the tree for a piece of data,
 * and if it is not found, returns a pointer to the node under which
 * it should be inserted.
 * \param tree  A pointer to the tree.
 * \param data  A pointer to the data for which to search.
 * \returns     `NULL` if the data was found and is already in the tree,
 * or a pointer to the last node tried if the data is not present.
 */

bs_tree_node bst_insert_search(bs_tree tree, void * data) {
    bs_tree_node searchnode = tree->root;
    bs_tree_node last_try = tree->root;
    bool found = false;

    /*  Return NULL if tree is empty  */

    if ( !searchnode ) {
        return NULL;
    }

    /*  Search tree for data  */

    while ( !found && searchnode ) {
        int compare = tree->cfunc(data, searchnode->data);
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
