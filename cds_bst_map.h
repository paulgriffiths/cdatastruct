/*!
 * \file            cds_bst_map.h
 * \brief           User interface to binary search tree map data structure.
 * \author          Paul Griffiths
 * \copyright       Copyright 2013 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */


#ifndef PG_CDS_BINARY_SEARCH_TREE_MAP_H
#define PG_CDS_BINARY_SEARCH_TREE_MAP_H

#include <stddef.h>


/*!
 * \brief           Typedef for map pointer.
 */

typedef struct bs_tree_t * bst_map;


/*  Function declarations  */

#ifdef __cplusplus
extern "C" {
#endif

bst_map bst_map_init(void);
void bst_map_free(bst_map map);

bool bst_map_isempty(const bst_map map);
size_t bst_map_length(const bst_map map);

bool bst_map_insert(bst_map map, const char * key, void * value);
bool bst_map_search(const bst_map map, const char * key);
void * bst_map_search_data(const bst_map map, const char * key);

void bst_map_lock(bst_map map);
void bst_map_unlock(bst_map map);

#ifdef __cplusplus
}
#endif


#endif          /*  PG_CDS_BINARY_SEARCH_TREE_MAP_H  */
