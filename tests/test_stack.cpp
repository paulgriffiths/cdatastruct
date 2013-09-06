/*
 *  test_stack.cpp
 *  ==============
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *  
 *  Unit tests for stack.
 *
 *  Uses Boost unit testing framework.
 *  
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */

#include <string>
#include <boost/test/unit_test.hpp>
#include "../cdatastruct.h"

BOOST_AUTO_TEST_SUITE(stack_suite)

BOOST_AUTO_TEST_CASE(stack_basic_test) {
    stack stk = stack_init();

    stack_push(stk, cds_new_int(4));
    stack_push(stk, cds_new_int(9));
    stack_push(stk, cds_new_int(16));

    BOOST_CHECK(stack_isempty(stk) == false);
    BOOST_CHECK(stack_length(stk) == 3);

    int * pval = (int *) stack_pop(stk);
    BOOST_CHECK(*pval == 16);
    BOOST_CHECK(stack_length(stk) == 2);
    free(pval);

    stack_free(stk);
}

BOOST_AUTO_TEST_SUITE_END()
