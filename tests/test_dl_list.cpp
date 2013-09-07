/*
 *  test_dl_list.cpp
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

BOOST_AUTO_TEST_SUITE(dl_list_suite)

BOOST_AUTO_TEST_CASE(dl_list_prepend_delete_front_test) {
    dl_list list = dl_list_init(cds_compare_uint, NULL);
    const unsigned int elems[] = {4, 9, 16, 25};
    for ( size_t i = 0; i < 4; ++i ) {
        dl_list_prepend(list, (void *) cds_new_uint(elems[i]));
    }

    BOOST_CHECK(dl_list_length(list) == 4);
    BOOST_CHECK_EQUAL(25, *((unsigned int*) dl_list_data(list, 0)));
    BOOST_CHECK_EQUAL(16, *((unsigned int*) dl_list_data(list, 1)));
    BOOST_CHECK_EQUAL(9, *((unsigned int*) dl_list_data(list, 2)));
    BOOST_CHECK_EQUAL(4, *((unsigned int*) dl_list_data(list, 3)));
    BOOST_CHECK(dl_list_isempty(list) == false);

    for ( size_t i = 0; i < 4; ++i ) {
        dl_list_delete_at(list, 0);
    }

    BOOST_CHECK(dl_list_length(list) == 0);
    BOOST_CHECK(dl_list_isempty(list) == true);

    dl_list_free(list);
}

BOOST_AUTO_TEST_CASE(dl_list_append_test) {
    dl_list list = dl_list_init(cds_compare_uint, NULL);
    const unsigned int elems[] = {4, 9, 16, 25};
    for ( size_t i = 0; i < 4; ++i ) {
        dl_list_append(list, (void *) cds_new_uint(elems[i]));
    }

    BOOST_CHECK(dl_list_length(list) == 4);
    BOOST_CHECK_EQUAL(4, *((unsigned int*) dl_list_data(list, 0)));
    BOOST_CHECK_EQUAL(9, *((unsigned int*) dl_list_data(list, 1)));
    BOOST_CHECK_EQUAL(16, *((unsigned int*) dl_list_data(list, 2)));
    BOOST_CHECK_EQUAL(25, *((unsigned int*) dl_list_data(list, 3)));
    BOOST_CHECK(dl_list_isempty(list) == false);

    dl_list_free(list);
}

BOOST_AUTO_TEST_CASE(dl_list_itr_from_index_test) {
    dl_list list = dl_list_init(cds_compare_uint, NULL);
    const unsigned int elems[] = {4, 9, 16, 25, 36, 49};
    for ( size_t i = 0; i < 6; ++i ) {
        dl_list_append(list, (void *) cds_new_uint(elems[i]));
    }

    BOOST_CHECK(dl_list_length(list) == 6);
    BOOST_CHECK(dl_list_isempty(list) == false);

    dl_list_itr itr = dl_list_itr_from_index(list, 0);
    BOOST_CHECK_EQUAL(4, *((unsigned int *) itr->data));

    itr = dl_list_itr_from_index(list, 1);
    BOOST_CHECK_EQUAL(9, *((unsigned int *) itr->data));

    itr = dl_list_itr_from_index(list, 2);
    BOOST_CHECK_EQUAL(16, *((unsigned int *) itr->data));

    itr = dl_list_itr_from_index(list, 3);
    BOOST_CHECK_EQUAL(25, *((unsigned int *) itr->data));

    itr = dl_list_itr_from_index(list, 4);
    BOOST_CHECK_EQUAL(36, *((unsigned int *) itr->data));

    itr = dl_list_itr_from_index(list, 5);
    BOOST_CHECK_EQUAL(49, *((unsigned int *) itr->data));

    dl_list_free(list);
}

BOOST_AUTO_TEST_CASE(dl_list_insert_before_test) {
    dl_list list = dl_list_init(cds_compare_uint, NULL);
    dl_list_append(list, (void *) cds_new_uint(4));

    const unsigned int elems[] = {9, 16, 25, 36};
    for ( size_t i = 0; i < 4; ++i ) {
        dl_list_itr itr = dl_list_first(list);
        dl_list_insert_before(list, itr, (void *) cds_new_uint(elems[i]));
    }

    BOOST_CHECK(dl_list_length(list) == 5);
    BOOST_CHECK_EQUAL(36, *((unsigned int*) dl_list_data(list, 0)));
    BOOST_CHECK_EQUAL(25, *((unsigned int*) dl_list_data(list, 1)));
    BOOST_CHECK_EQUAL(16, *((unsigned int*) dl_list_data(list, 2)));
    BOOST_CHECK_EQUAL(9, *((unsigned int*) dl_list_data(list, 3)));
    BOOST_CHECK_EQUAL(4, *((unsigned int*) dl_list_data(list, 4)));
    BOOST_CHECK(dl_list_isempty(list) == false);

    dl_list_free(list);
}

BOOST_AUTO_TEST_CASE(dl_list_insert_at_back_test) {
    dl_list list = dl_list_init(cds_compare_uint, NULL);

    const unsigned int elems[] = {4, 9, 16, 25, 36};
    for ( size_t i = 0; i < 5; ++i ) {
        size_t list_len = dl_list_length(list);
        dl_list_insert_at(list, list_len, (void *) cds_new_uint(elems[i]));
    }

    BOOST_CHECK(dl_list_length(list) == 5);
    BOOST_CHECK_EQUAL(4, *((unsigned int*) dl_list_data(list, 0)));
    BOOST_CHECK_EQUAL(9, *((unsigned int*) dl_list_data(list, 1)));
    BOOST_CHECK_EQUAL(16, *((unsigned int*) dl_list_data(list, 2)));
    BOOST_CHECK_EQUAL(25, *((unsigned int*) dl_list_data(list, 3)));
    BOOST_CHECK_EQUAL(36, *((unsigned int*) dl_list_data(list, 4)));
    BOOST_CHECK(dl_list_isempty(list) == false);

    dl_list_free(list);
}

BOOST_AUTO_TEST_CASE(dl_list_add_delete_back_test) {
    dl_list list = dl_list_init(cds_compare_ulong, NULL);
    const unsigned long elems[] = {4, 9, 16, 25};
    for ( size_t i = 0; i < 4; ++i ) {
        dl_list_insert_at(list, i, (void *) cds_new_ulong(elems[i]));
    }

    BOOST_CHECK(dl_list_length(list) == 4);
    BOOST_CHECK_EQUAL(4, *((unsigned long*) dl_list_data(list, 0)));
    BOOST_CHECK_EQUAL(9, *((unsigned long*) dl_list_data(list, 1)));
    BOOST_CHECK_EQUAL(16, *((unsigned long*) dl_list_data(list, 2)));
    BOOST_CHECK_EQUAL(25, *((unsigned long*) dl_list_data(list, 3)));
    BOOST_CHECK(dl_list_isempty(list) == false);

    for ( size_t i = 4; i > 0; --i ) {
        dl_list_delete_at(list, i - 1);
    }

    BOOST_CHECK(dl_list_length(list) == 0);
    BOOST_CHECK(dl_list_isempty(list) == true);

    dl_list_free(list);
}

BOOST_AUTO_TEST_CASE(dl_list_itr_get_data_test) {
    dl_list list = dl_list_init(cds_compare_string, NULL);
    const char * elems[] = {"spam", "eggs", "bacon", "toffee", "gruel"};
    for ( size_t i = 0; i < 5; ++i ) {
        dl_list_insert_at(list, i, (void *) cds_new_string(elems[i]));
    }

    dl_list_itr itr = dl_list_first(list);
    for ( int i = 0; i < 3; ++i ) {
        itr = dl_list_next(itr);
    }

    std::string expected_result("toffee");
    std::string test_result((char *) itr->data);
    BOOST_CHECK_EQUAL(expected_result, test_result);
    
    dl_list_free(list);
}

BOOST_AUTO_TEST_CASE(dl_list_find_insert_itr_test) {
    dl_list list = dl_list_init(cds_compare_string, NULL);
    const int elems[] = {4, 9, 16, 25, 36, 49};
    for ( size_t i = 0; i < 6; ++i ) {
        dl_list_insert_at(list, i, (void *) cds_new_int(elems[i]));
    }

    BOOST_CHECK_EQUAL(4, *((int *) dl_list_data(list, 0)));
    BOOST_CHECK_EQUAL(9, *((int *) dl_list_data(list, 1)));
    BOOST_CHECK_EQUAL(16, *((int *) dl_list_data(list, 2)));
    BOOST_CHECK_EQUAL(25, *((int *) dl_list_data(list, 3)));
    BOOST_CHECK_EQUAL(36, *((int *) dl_list_data(list, 4)));
    BOOST_CHECK_EQUAL(49, *((int *) dl_list_data(list, 5)));
    BOOST_CHECK(dl_list_length(list) == 6);
    BOOST_CHECK(dl_list_isempty(list) == false);

    int search_item = 15;
    dl_list_itr itr = dl_list_find_itr(list, &search_item);
    BOOST_CHECK(itr == NULL);

    search_item = 25;
    itr = dl_list_find_itr(list, &search_item);
    BOOST_CHECK(itr != NULL);
    
    int result = dl_list_insert_after(list, itr, cds_new_int(99));
    BOOST_CHECK(result == 0);
    BOOST_CHECK(dl_list_length(list) == 7);
    BOOST_CHECK_EQUAL(25, *((int *) dl_list_data(list, 3)));
    BOOST_CHECK_EQUAL(99, *((int *) dl_list_data(list, 4)));
    BOOST_CHECK_EQUAL(36, *((int *) dl_list_data(list, 5)));
    BOOST_CHECK_EQUAL(49, *((int *) dl_list_data(list, 6)));

    itr = dl_list_itr_from_index(list, 5);
    BOOST_CHECK_EQUAL(36, *((long *) itr->data));
    dl_list_free(list);
}

BOOST_AUTO_TEST_CASE(dl_list_find_insert_index_test) {
    dl_list list = dl_list_init(cds_compare_string, NULL);
    const long elems[] = {4, 9, 16, 25, 36, 49};
    for ( size_t i = 0; i < 6; ++i ) {
        dl_list_insert_at(list, i, (void *) cds_new_long(elems[i]));
    }

    BOOST_CHECK_EQUAL(4, *((int *) dl_list_data(list, 0)));
    BOOST_CHECK_EQUAL(9, *((int *) dl_list_data(list, 1)));
    BOOST_CHECK_EQUAL(16, *((int *) dl_list_data(list, 2)));
    BOOST_CHECK_EQUAL(25, *((int *) dl_list_data(list, 3)));
    BOOST_CHECK_EQUAL(36, *((int *) dl_list_data(list, 4)));
    BOOST_CHECK_EQUAL(49, *((int *) dl_list_data(list, 5)));
    BOOST_CHECK(dl_list_length(list) == 6);
    BOOST_CHECK(dl_list_isempty(list) == false);

    long search_item = 15;
    int index = dl_list_find_index(list, &search_item);
    BOOST_CHECK(index < 0);

    search_item = 25;
    index = dl_list_find_index(list, &search_item);
    BOOST_CHECK(index == 3);
    
    int result = dl_list_insert_at(list, index + 1, cds_new_int(99));
    BOOST_CHECK(result == 0);
    BOOST_CHECK(dl_list_length(list) == 7);
    BOOST_CHECK_EQUAL(25, *((long *) dl_list_data(list, 3)));
    BOOST_CHECK_EQUAL(99, *((long *) dl_list_data(list, 4)));
    BOOST_CHECK_EQUAL(36, *((long *) dl_list_data(list, 5)));
    BOOST_CHECK_EQUAL(49, *((long *) dl_list_data(list, 6)));

    dl_list_free(list);
}

BOOST_AUTO_TEST_SUITE_END()
