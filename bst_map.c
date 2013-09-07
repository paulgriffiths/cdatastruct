/*!
 * \file            bst_map.c
 * \brief           Implementation of binary search tree map data structure.
 * \author          Paul Griffiths
 * \copyright       Copyright 2013 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */


#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <paulgrif/chelpers.h>
#include "cds_common.h"
#include "cds_bst_map.h"
#include "bs_tree.h"


/*!
 * \brief           Key-value pair struct.
 */

typedef struct kvpair_t {
    char * key;           /*!< Key string */
    void * value;               /*!< Pointer to data */
} kvpair_t;


/*!
 * \brief           Typedef for kvpair pointer.
 */

typedef struct kvpair_t * kvpair;


/*!
 * \brief           Constructs a new kvpair.
 * \param key       The key for the new pair.
 * \param value     Pointer to the value for the new pair.
 * \returns         A pointer for the new pair.
 */

static void * new_kvpair(const char * key, void * value) {
    kvpair pair = term_malloc(sizeof(*pair));
    pair->key = term_strdup(key);
    pair->value = value;
    return pair;
}


/*!
 * \brief           Frees resources used by a kvpair.
 * \param pair      A pointer to the kvpair to free.
 */

static void free_kvpair(void * pair) {
    kvpair rm_kvpair = pair;
    free(rm_kvpair->key);
    free(rm_kvpair->value);
    free(rm_kvpair);
}


/*!
 * \brief           Compare the keys of two kvpairs.
 * \param data      `void` pointer to kvpair to be compared.
 * \param cmp       `void` pointer to comparison kvpair.
 * \returns         -1 if the key of data is less than the key of cmp,
 * 1 if the key of data is greater than the key of cmp, and 0 if the
 * two keys are equal.
 */

static int compare_kvpair(const void * data, const void * cmp) {
    const kvpair pair_data = (const kvpair) data;
    const kvpair pair_cmp = (const kvpair) cmp;
    return strcmp(pair_data->key, pair_cmp->key);
}


/*!
 * \brief           Initializes a new binary search tree map.
 * \returns         A pointer to the new map.
 */

bst_map bst_map_init(void) {
    bst_map new_map = bs_tree_init(compare_kvpair, free_kvpair);
    return new_map;
}


/*!
 * \brief           Frees the resources associated with a BST map.
 * \param map       A pointer to the map to free.
 */

void bst_map_free(bst_map map) {
    bs_tree_free(map);
}


/*!
 * \brief           Returns the number of elements in a BST map.
 * \param map       A pointer to the map.
 * \returns         The number of elements in the map.
 */

size_t bst_map_length(const bst_map map) {
    return bs_tree_length(map);
}


/*!
 * \brief           Checks if a map is empty.
 * \param map       A pointer to the map.
 * \returns         `true` if the map is empty, otherwise `false`.
 */

bool bst_map_isempty(const bst_map map) {
    return bs_tree_isempty(map);
}


/*!
 * \brief           Determines if a key is in a map.
 * \param map       A pointer to the map.
 * \param key       The key for which to search.
 * \returns         `true` is the key is found, `false` otherwise.
 */

bool bst_map_search(const bst_map map, const char * key) {

    /*  key is cast to (char *) to match data member of kvpair,
        safe since `pair` itself is declared `const`, and passed
        to bs_tree_search_node() which accepts a `const` pointer.  */

    const kvpair_t pair = {(char *) key, NULL};
    bs_tree_node node = bs_tree_search_node(map, &pair);
    return node ? true : false;
}


/*!
 * \brief           Searches a map for a value matching a key and returns it.
 * \param map       A pointer to the map.
 * \param key       The key for which to search.
 * \returns         A pointer to the value if found, `NULL` otherwise.
 */

void * bst_map_search_data(const bst_map map, const char * key) {

    /*  key is cast to (char *) to match data member of kvpair,
        safe since `pair` itself is declared `const`, and passed
        to bs_tree_search_node() which accepts a `const` pointer.  */

    const kvpair_t pair = {(char *) key, NULL};
    void * return_value;
    bs_tree_node node = bs_tree_search_node(map, &pair);

    if ( node ) {
        kvpair ret_pair = (kvpair) node->data;
        return_value = ret_pair->value;
    } else {
        return_value = NULL;
    }

    return return_value;
}


/*!
 * \brief           Inserts a key-value pair into a map.
 * \details         The value is replaced if the key is already found
 * in the map. Any memory consumed by the old value is automatically
 * `free()`d.
 * \param map       A pointer to the map.
 * \param key       The key of the new value to insert.
 * \param value     A pointer to the new value to insert.
 * \returns         `true` if the key was already in the tree and the
 * value has been replaced, `false` if the key was not present.
 */

bool bst_map_insert(bst_map map, const char * key, void * value) {
    kvpair new_pair = new_kvpair(key, value);
    return bs_tree_insert_subtree(map, &map->root, new_pair);
}
