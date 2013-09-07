/*
 *  test_sl_list.cpp
 *  ================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *  
 *  Unit tests for singly linked list.
 *
 *  Uses Boost unit testing framework.
 *  
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */

#include <string>
#include <boost/test/unit_test.hpp>
#include "../cdatastruct.h"

BOOST_AUTO_TEST_SUITE(sl_list_suite)

BOOST_AUTO_TEST_CASE(sl_list_prepend_delete_front_test) {
    sl_list list = sl_list_init(cds_compare_uint, NULL);
    const unsigned int elems[] = {4, 9, 16, 25};
    for ( size_t i = 0; i < 4; ++i ) {
        sl_list_prepend(list, (void *) cds_new_uint(elems[i]));
    }

    BOOST_CHECK(sl_list_length(list) == 4);
    BOOST_CHECK_EQUAL(25, *((unsigned int*) sl_list_data(list, 0)));
    BOOST_CHECK_EQUAL(16, *((unsigned int*) sl_list_data(list, 1)));
    BOOST_CHECK_EQUAL(9, *((unsigned int*) sl_list_data(list, 2)));
    BOOST_CHECK_EQUAL(4, *((unsigned int*) sl_list_data(list, 3)));
    BOOST_CHECK(sl_list_isempty(list) == false);

    for ( size_t i = 0; i < 4; ++i ) {
        sl_list_delete_at(list, 0);
    }

    BOOST_CHECK(sl_list_length(list) == 0);
    BOOST_CHECK(sl_list_isempty(list) == true);

    sl_list_free(list);
}

BOOST_AUTO_TEST_CASE(sl_list_add_delete_back_test) {
    sl_list list = sl_list_init(cds_compare_ulong, NULL);
    const unsigned long elems[] = {4, 9, 16, 25};
    for ( size_t i = 0; i < 4; ++i ) {
        sl_list_insert_at(list, i, (void *) cds_new_ulong(elems[i]));
    }

    BOOST_CHECK(sl_list_length(list) == 4);
    BOOST_CHECK_EQUAL(4, *((unsigned long*) sl_list_data(list, 0)));
    BOOST_CHECK_EQUAL(9, *((unsigned long*) sl_list_data(list, 1)));
    BOOST_CHECK_EQUAL(16, *((unsigned long*) sl_list_data(list, 2)));
    BOOST_CHECK_EQUAL(25, *((unsigned long*) sl_list_data(list, 3)));
    BOOST_CHECK(sl_list_isempty(list) == false);

    for ( size_t i = 4; i > 0; --i ) {
        sl_list_delete_at(list, i - 1);
    }

    BOOST_CHECK(sl_list_length(list) == 0);
    BOOST_CHECK(sl_list_isempty(list) == true);

    sl_list_free(list);
}

BOOST_AUTO_TEST_CASE(sl_list_itr_get_data_test) {
    sl_list list = sl_list_init(cds_compare_string, NULL);
    const char * elems[] = {"spam", "eggs", "bacon", "toffee", "gruel"};
    for ( size_t i = 0; i < 5; ++i ) {
        sl_list_insert_at(list, i, (void *) cds_new_string(elems[i]));
    }

    sl_list_itr itr = sl_list_first(list);
    for ( int i = 0; i < 3; ++i ) {
        itr = sl_list_next(itr);
    }

    std::string expected_result("toffee");
    std::string test_result((char *) itr->data);
    BOOST_CHECK_EQUAL(expected_result, test_result);
    
    sl_list_free(list);
}

BOOST_AUTO_TEST_CASE(sl_list_find_insert_itr_test) {
    sl_list list = sl_list_init(cds_compare_string, NULL);
    const int elems[] = {4, 9, 16, 25, 36, 49};
    for ( size_t i = 0; i < 6; ++i ) {
        sl_list_insert_at(list, i, (void *) cds_new_int(elems[i]));
    }

    BOOST_CHECK_EQUAL(4, *((int *) sl_list_data(list, 0)));
    BOOST_CHECK_EQUAL(9, *((int *) sl_list_data(list, 1)));
    BOOST_CHECK_EQUAL(16, *((int *) sl_list_data(list, 2)));
    BOOST_CHECK_EQUAL(25, *((int *) sl_list_data(list, 3)));
    BOOST_CHECK_EQUAL(36, *((int *) sl_list_data(list, 4)));
    BOOST_CHECK_EQUAL(49, *((int *) sl_list_data(list, 5)));
    BOOST_CHECK(sl_list_length(list) == 6);
    BOOST_CHECK(sl_list_isempty(list) == false);

    int search_item = 15;
    sl_list_itr itr = sl_list_find_itr(list, &search_item);
    BOOST_CHECK(itr == NULL);

    search_item = 25;
    itr = sl_list_find_itr(list, &search_item);
    BOOST_CHECK(itr != NULL);
    
    int result = sl_list_insert_after(list, itr, cds_new_int(99));
    BOOST_CHECK(result == 0);
    BOOST_CHECK(sl_list_length(list) == 7);
    BOOST_CHECK_EQUAL(25, *((int *) sl_list_data(list, 3)));
    BOOST_CHECK_EQUAL(99, *((int *) sl_list_data(list, 4)));
    BOOST_CHECK_EQUAL(36, *((int *) sl_list_data(list, 5)));
    BOOST_CHECK_EQUAL(49, *((int *) sl_list_data(list, 6)));

    itr = sl_list_itr_from_index(list, 5);
    BOOST_CHECK_EQUAL(36, *((long *) itr->data));
    sl_list_free(list);
}

BOOST_AUTO_TEST_CASE(sl_list_find_insert_index_test) {
    sl_list list = sl_list_init(cds_compare_string, NULL);
    const long elems[] = {4, 9, 16, 25, 36, 49};
    for ( size_t i = 0; i < 6; ++i ) {
        sl_list_insert_at(list, i, (void *) cds_new_long(elems[i]));
    }

    BOOST_CHECK_EQUAL(4, *((int *) sl_list_data(list, 0)));
    BOOST_CHECK_EQUAL(9, *((int *) sl_list_data(list, 1)));
    BOOST_CHECK_EQUAL(16, *((int *) sl_list_data(list, 2)));
    BOOST_CHECK_EQUAL(25, *((int *) sl_list_data(list, 3)));
    BOOST_CHECK_EQUAL(36, *((int *) sl_list_data(list, 4)));
    BOOST_CHECK_EQUAL(49, *((int *) sl_list_data(list, 5)));
    BOOST_CHECK(sl_list_length(list) == 6);
    BOOST_CHECK(sl_list_isempty(list) == false);

    long search_item = 15;
    int index = sl_list_find_index(list, &search_item);
    BOOST_CHECK(index < 0);

    search_item = 25;
    index = sl_list_find_index(list, &search_item);
    BOOST_CHECK(index == 3);
    
    int result = sl_list_insert_at(list, index + 1, cds_new_int(99));
    BOOST_CHECK(result == 0);
    BOOST_CHECK(sl_list_length(list) == 7);
    BOOST_CHECK_EQUAL(25, *((long *) sl_list_data(list, 3)));
    BOOST_CHECK_EQUAL(99, *((long *) sl_list_data(list, 4)));
    BOOST_CHECK_EQUAL(36, *((long *) sl_list_data(list, 5)));
    BOOST_CHECK_EQUAL(49, *((long *) sl_list_data(list, 6)));

    sl_list_free(list);
}

BOOST_AUTO_TEST_SUITE_END()
