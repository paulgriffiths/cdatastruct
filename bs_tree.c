/*!
 * \file            bs_tree.c
 * \brief           Implementation of binary search tree data structure.
 * \author          Paul Griffiths
 * \copyright       Copyright 2013 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <paulgrif/chelpers.h>
#include "cds_common.h"
#include "bs_tree.h"


#ifdef CDS_THREAD_SUPPORT
  #include <pthread.h>
#endif


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

#ifdef CDS_THREAD_SUPPORT
    int status = pthread_mutex_init(&new_tree->mutex, NULL);
    if ( status != 0 ) {
        fputs("cdatastruct error: couldn't initialize mutex", stderr);
        exit(EXIT_FAILURE);
    }
#endif

    return new_tree;
}


/*!
 * \brief           Frees the resources associated with a tree.
 * \param tree      A pointer to the tree to free.
 */

void bs_tree_free(bs_tree tree) {
    bs_tree_free_subtree(tree, tree->root);

#ifdef CDS_THREAD_SUPPORT
    int status = pthread_mutex_destroy(&tree->mutex);
    if ( status != 0 ) {
        fputs("cdatastruct error: couldn't destroy mutex", stderr);
    }
#endif

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
 * \brief           Determines if a data element is in a tree.
 * \param tree      A pointer to the tree.
 * \param data      The data for which to search.
 * \returns         `true` is the data is found, `false` otherwise.
 */

bool bs_tree_search(const bs_tree tree, const void * data) {
    const bs_tree_node node = bs_tree_search_node(tree, data);
    return node ? true : false;
}


/*!
 * \brief           Searches a tree for a piece of data and returns it.
 * \param tree      A pointer to the tree.
 * \param data      The data for which to search.
 * \returns         A pointer to the data if found, `NULL` otherwise.
 */

void * bs_tree_search_data(const bs_tree tree, const void * data) {
    void * return_data;
    bs_tree_node node = bs_tree_search_node(tree, data);
    if ( node ) {
        return_data = node->data;
    } else {
        return_data = NULL;
    }

    return return_data;
}


/*!
 * \brief           Inserts data into a tree.
 * \details         Duplicated data is replaced. This is a superfluous
 * operation for scalar data, but is necessary for structs, where
 * 'found' may mean only one element of the struct compares equal,
 * and other elements may be different (e.g. a map data structure).
 * \param tree      A pointer to the tree.
 * \param data      The data to insert.
 * \returns         `true` if the data was already in the tree and has
 * been replaced, `false` if it was not present and newly added.
 */

bool bs_tree_insert(bs_tree tree, void * data) {
    return bs_tree_insert_subtree(tree, &tree->root, data);
}


/*!
 * \brief           Performs a preorder left-to-right traversal of a bs_tree.
 * \param tree      A pointer to the tree.
 * \param dfunc     A pointer to the function to invoke for each node.
 * \param arg       A pointer to the argument to pass to `dfunc()`.
 */

void bs_tree_preorder_left_traverse(bs_tree tree,
        void (*dfunc)(void *, void * arg), void * arg) {
    if ( tree ) {
        bs_tree_preorder_left_traverse_int(tree, tree->root, dfunc, arg);
    }
}


/*!
 * \brief           Performs an inorder left-to-right traversal of a bs_tree.
 * \param tree      A pointer to the tree.
 * \param dfunc     A pointer to the function to invoke for each node.
 * \param arg       A pointer to the argument to pass to `dfunc()`.
 */

void bs_tree_inorder_left_traverse(bs_tree tree,
        void (*dfunc)(void *, void * arg), void * arg) {
    if ( tree ) {
        bs_tree_inorder_left_traverse_int(tree, tree->root, dfunc, arg);
    }
}


/*!
 * \brief           Performs a postorder left-to-right traversal of a bs_tree.
 * \param tree      A pointer to the tree.
 * \param dfunc     A pointer to the function to invoke for each node.
 * \param arg       A pointer to the argument to pass to `dfunc()`.
 */

void bs_tree_postorder_left_traverse(bs_tree tree,
        void (*dfunc)(void *, void * arg), void * arg) {
    if ( tree ) {
        bs_tree_postorder_left_traverse_int(tree, tree->root, dfunc, arg);
    }
}


/*!
 * \brief           Performs a preorder right-to-left traversal of a bs_tree.
 * \param tree      A pointer to the tree.
 * \param dfunc     A pointer to the function to invoke for each node.
 * \param arg       A pointer to the argument to pass to `dfunc()`.
 */

void bs_tree_preorder_right_traverse(bs_tree tree,
        void (*dfunc)(void *, void * arg), void * arg) {
    if ( tree ) {
        bs_tree_preorder_right_traverse_int(tree, tree->root, dfunc, arg);
    }
}


/*!
 * \brief           Performs an inorder right-to-left traversal of a bs_tree.
 * \param tree      A pointer to the tree.
 * \param dfunc     A pointer to the function to invoke for each node.
 * \param arg       A pointer to the argument to pass to `dfunc()`.
 */

void bs_tree_inorder_right_traverse(bs_tree tree,
        void (*dfunc)(void *, void * arg), void * arg) {
    if ( tree ) {
        bs_tree_inorder_right_traverse_int(tree, tree->root, dfunc, arg);
    }
}


/*!
 * \brief           Performs a postorder right-to-left traversal of a bs_tree.
 * \param tree      A pointer to the tree.
 * \param dfunc     A pointer to the function to invoke for each node.
 * \param arg       A pointer to the argument to pass to `dfunc()`.
 */

void bs_tree_postorder_right_traverse(bs_tree tree,
        void (*dfunc)(void *, void * arg), void * arg) {
    if ( tree ) {
        bs_tree_postorder_right_traverse_int(tree, tree->root, dfunc, arg);
    }
}


/*!
 * \brief           Locks a tree's mutex.
 * \param tree      A pointer to the tree.
 */

void bs_tree_lock(bs_tree tree) {
#ifdef CDS_THREAD_SUPPORT
    int status = pthread_mutex_lock(&tree->mutex);
    if ( status != 0 ) {
        fputs("cdatastruct error: couldn't lock mutex.", stderr);
        exit(EXIT_FAILURE);
    }
#else
    (void) tree;        /*  Avoid unused parameter warning  */
#endif
}


/*!
 * \brief           Unlocks a tree's mutex.
 * \param tree      A pointer to the tree.
 */

void bs_tree_unlock(bs_tree tree) {
#ifdef CDS_THREAD_SUPPORT
    int status = pthread_mutex_unlock(&tree->mutex);
    if ( status != 0 ) {
        fputs("cdatastruct error: couldn't lock mutex.", stderr);
        exit(EXIT_FAILURE);
    }
#else
    (void) tree;        /*  Avoid unused parameter warning  */
#endif
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

bs_tree_node bs_tree_search_node(const bs_tree tree, const void * data) {
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
 * \details         The data element is replaced if it is found in the tree.
 * This is a superfluous operation for scalar data, but is necessary for
 * structs, where 'found' may mean only one of the struct members compares
 * equal, and other data elements may differ. This function `free()`s the
 * old data when this happens.
 * \param tree      A pointer to the tree
 * \param p_node    A pointer to the pointer to the node at the root of the
 * subtree.
 * \param data      A pointer to the data to which to insert.
 * \returns         `true` if the data was present and duplicated,
 * 'false' if not.
 */

bool bs_tree_insert_subtree(bs_tree tree, bs_tree_node * p_node, void * data) {
    bool duplicate = false;

    if ( *p_node ) {
        bs_tree_node node = bs_tree_insert_search(tree, data, &duplicate);

        if ( !duplicate ) {
            bs_tree_node new_node = bs_tree_new_node(data);
            int compare = tree->cfunc(data, node->data);
            if ( compare < 0 ) {
                node->left = new_node;
            } else {
                node->right = new_node;
            }
            ++tree->length;
        } else {
            tree->free_func(node->data);
            node->data = data;
        }
    } else {
        
        /*  Tree is empty  */

        bs_tree_node new_node = bs_tree_new_node(data);
        *p_node = new_node;
        ++tree->length;
    }

    return duplicate;
}


/*!
 * \brief       Searches a tree for insertion purposes.
 * \details     The function searches the tree for a piece of data,
 * and if it is not found, returns a pointer to the node under which
 * it should be inserted.
 * \param tree  A pointer to the tree.
 * \param data  A pointer to the data for which to search.
 * \param found A pointer to a `bool` to populate according to whether
 * the data is already in the tree.
 * \returns     A pointer to the node in which the data was found, if
 * it was found, or a pointer to the last node tried if it was not.
 * The last tried node is the one under which the new data should be
 * inserted, if it is not already in the tree.
 */

bs_tree_node bs_tree_insert_search(bs_tree tree, void * data, bool * found) {
    bs_tree_node searchnode = tree->root;
    bs_tree_node last_try = tree->root;
    *found = false;

    /*  Return NULL if tree is empty  */

    if ( !searchnode ) {
        return NULL;
    }

    /*  Search tree for data  */

    while ( !(*found) && searchnode ) {
        int compare = tree->cfunc(data, searchnode->data);
        if ( !compare ) {
            *found = true;
        } else if ( compare < 0 ) {
            last_try = searchnode;
            searchnode = searchnode->left;
        } else {
            last_try = searchnode;
            searchnode = searchnode->right;
        }
    }

    return (*found) ? searchnode : last_try;
}


/*!
 * \brief           Performs a preorder left-to-right traversal of a bs_tree.
 * \details         This function is called internally by the matching
 * function that the library user calls.
 * \param tree      A pointer to the tree.
 * \param node      A pointer to the current node.
 * \param dfunc     A pointer to the function to invoke for each node.
 * \param arg       A pointer to the argument to pass to `dfunc()`.
 */

void bs_tree_preorder_left_traverse_int(bs_tree tree, bs_tree_node node,
        void (*dfunc)(void *, void *), void * arg) {
    if ( node ) {
        dfunc(node->data, arg);
        bs_tree_preorder_left_traverse_int(tree, node->left, dfunc, arg);
        bs_tree_preorder_left_traverse_int(tree, node->right, dfunc, arg);
    }
}


/*!
 * \brief           Performs an inorder left-to-right traversal of a bs_tree.
 * \details         This function is called internally by the matching
 * function that the library user calls.
 * \param tree      A pointer to the tree.
 * \param node      A pointer to the current node.
 * \param dfunc     A pointer to the function to invoke for each node.
 * \param arg       A pointer to the argument to pass to `dfunc()`.
 */

void bs_tree_inorder_left_traverse_int(bs_tree tree, bs_tree_node node,
        void (*dfunc)(void *, void *), void * arg) {
    if ( node ) {
        bs_tree_inorder_left_traverse_int(tree, node->left, dfunc, arg);
        dfunc(node->data, arg);
        bs_tree_inorder_left_traverse_int(tree, node->right, dfunc, arg);
    }
}


/*!
 * \brief           Performs a postorder left-to-right traversal of a bs_tree.
 * \details         This function is called internally by the matching
 * function that the library user calls.
 * \param tree      A pointer to the tree.
 * \param node      A pointer to the current node.
 * \param dfunc     A pointer to the function to invoke for each node.
 * \param arg       A pointer to the argument to pass to `dfunc()`.
 */

void bs_tree_postorder_left_traverse_int(bs_tree tree, bs_tree_node node,
        void (*dfunc)(void *, void *), void * arg) {
    if ( node ) {
        bs_tree_postorder_left_traverse_int(tree, node->left, dfunc, arg);
        bs_tree_postorder_left_traverse_int(tree, node->right, dfunc, arg);
        dfunc(node->data, arg);
    }
}


/*!
 * \brief           Performs a preorder right-to-left traversal of a bs_tree.
 * \details         This function is called internally by the matching
 * function that the library user calls.
 * \param tree      A pointer to the tree.
 * \param node      A pointer to the current node.
 * \param dfunc     A pointer to the function to invoke for each node.
 * \param arg       A pointer to the argument to pass to `dfunc()`.
 */

void bs_tree_preorder_right_traverse_int(bs_tree tree, bs_tree_node node,
        void (*dfunc)(void *, void *), void * arg) {
    if ( node ) {
        dfunc(node->data, arg);
        bs_tree_preorder_right_traverse_int(tree, node->right, dfunc, arg);
        bs_tree_preorder_right_traverse_int(tree, node->left, dfunc, arg);
    }
}


/*!
 * \brief           Performs an inorder right-to-left traversal of a bs_tree.
 * \details         This function is called internally by the matching
 * function that the library user calls.
 * \param tree      A pointer to the tree.
 * \param node      A pointer to the current node.
 * \param dfunc     A pointer to the function to invoke for each node.
 * \param arg       A pointer to the argument to pass to `dfunc()`.
 */

void bs_tree_inorder_right_traverse_int(bs_tree tree, bs_tree_node node,
        void (*dfunc)(void *, void *), void * arg) {
    if ( node ) {
        bs_tree_inorder_right_traverse_int(tree, node->right, dfunc, arg);
        dfunc(node->data, arg);
        bs_tree_inorder_right_traverse_int(tree, node->left, dfunc, arg);
    }
}


/*!
 * \brief           Performs a postorder right-to-left traversal of a bs_tree.
 * \details         This function is called internally by the matching
 * function that the library user calls.
 * \param tree      A pointer to the tree.
 * \param node      A pointer to the current node.
 * \param dfunc     A pointer to the function to invoke for each node.
 * \param arg       A pointer to the argument to pass to `dfunc()`.
 */

void bs_tree_postorder_right_traverse_int(bs_tree tree, bs_tree_node node,
        void (*dfunc)(void *, void *), void * arg) {
    if ( node ) {
        bs_tree_postorder_right_traverse_int(tree, node->right, dfunc, arg);
        bs_tree_postorder_right_traverse_int(tree, node->left, dfunc, arg);
        dfunc(node->data, arg);
    }
}
