/*
 *  test_bs_tree.cpp
 *  ================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *  
 *  Unit tests for binary search tree.
 *
 *  Uses Boost unit testing framework.
 *  
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */

#include <string>
#include <boost/test/unit_test.hpp>
#include "../cdatastruct.h"

BOOST_AUTO_TEST_SUITE(bs_tree_suite)

BOOST_AUTO_TEST_CASE(bs_tree_insert_search_test) {
    bs_tree tree = bs_tree_init(cds_compare_string);

    bs_tree_insert(tree, cds_new_string("bacon"));
    bs_tree_insert(tree, cds_new_string("eggs"));
    bs_tree_insert(tree, cds_new_string("spam"));
    bs_tree_insert(tree, cds_new_string("cheese"));
    bs_tree_insert(tree, cds_new_string("gruel"));

    BOOST_CHECK_EQUAL(bs_tree_length(tree), 5);
    bool test_result;

    test_result = bs_tree_search(tree, (void *) "bacon");
    BOOST_CHECK(test_result == true);

    test_result = bs_tree_search(tree, (void *) "cheese");
    BOOST_CHECK(test_result == true);

    test_result = bs_tree_search(tree, (void *) "gruel");
    BOOST_CHECK(test_result == true);

    test_result = bs_tree_search(tree, (void *) "goats");
    BOOST_CHECK(test_result == false);

    test_result = bs_tree_search(tree, (void *) "chips");
    BOOST_CHECK(test_result == false);

    bs_tree_free(tree);
}

BOOST_AUTO_TEST_CASE(bs_tree_insert_existing_test) {
    bs_tree tree = bs_tree_init(cds_compare_string);

    bs_tree_insert(tree, cds_new_string("bacon"));
    bs_tree_insert(tree, cds_new_string("eggs"));
    bs_tree_insert(tree, cds_new_string("spam"));
    bs_tree_insert(tree, cds_new_string("cheese"));
    bs_tree_insert(tree, cds_new_string("gruel"));

    BOOST_CHECK_EQUAL(bs_tree_length(tree), 5);

    bool test_result;

    void * data = cds_new_string("spam");
    test_result = bs_tree_insert(tree, data);
    BOOST_CHECK(test_result == false);

    BOOST_CHECK_EQUAL(bs_tree_length(tree), 5);

    free(data);
    bs_tree_free(tree);
}

BOOST_AUTO_TEST_SUITE_END()
