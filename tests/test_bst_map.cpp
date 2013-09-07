/*
 *  test_bst_map.cpp
 *  ================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *  
 *  Unit tests for binary search tree map.
 *
 *  Uses Boost unit testing framework.
 *  
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */

#include <string>
#include <boost/test/unit_test.hpp>
#include "../cdatastruct.h"

BOOST_AUTO_TEST_SUITE(bst_map_suite)

BOOST_AUTO_TEST_CASE(bst_map_insert_search_test) {
    bst_map map = bst_map_init();

    bst_map_insert(map, "bacon", cds_new_int(4));
    bst_map_insert(map, "eggs", cds_new_int(9));
    bst_map_insert(map, "spam", cds_new_int(16));
    bst_map_insert(map, "cheese", cds_new_int(25));
    bst_map_insert(map, "gruel", cds_new_int(36));

    BOOST_CHECK_EQUAL(bst_map_length(map), 5);
    
    int * pval = (int *) bst_map_search_data(map, "spam");
    BOOST_CHECK_EQUAL(*pval, 16);

    bool found = bst_map_search(map, "frosties");
    BOOST_CHECK(found == false);

    bst_map_free(map);
}

BOOST_AUTO_TEST_CASE(bst_map_insert_replace_test) {
    bst_map map = bst_map_init();

    bst_map_insert(map, "bacon", cds_new_int(4));
    bst_map_insert(map, "eggs", cds_new_int(9));
    bst_map_insert(map, "spam", cds_new_int(16));
    bst_map_insert(map, "cheese", cds_new_int(25));
    bst_map_insert(map, "gruel", cds_new_int(36));

    BOOST_CHECK_EQUAL(bst_map_length(map), 5);
    
    int * pval = (int *) bst_map_search_data(map, "spam");
    BOOST_CHECK_EQUAL(*pval, 16);

    bool duplicate = bst_map_insert(map, "spam", cds_new_int(99));
    BOOST_CHECK(duplicate);
    
    pval = (int *) bst_map_search_data(map, "spam");
    BOOST_CHECK_EQUAL(*pval, 99);

    BOOST_CHECK_EQUAL(bst_map_length(map), 5);

    bst_map_free(map);
}

BOOST_AUTO_TEST_SUITE_END()
