/*
 *  test_queue.cpp
 *  ==============
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *  
 *  Unit tests for queue.
 *
 *  Uses Boost unit testing framework.
 *  
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */

#include <string>
#include <boost/test/unit_test.hpp>
#include "../cdatastruct.h"

BOOST_AUTO_TEST_SUITE(queue_suite)

BOOST_AUTO_TEST_CASE(queue_basic_test) {
    queue que = queue_init(NULL);

    queue_pushback(que, cds_new_int(4));
    queue_pushback(que, cds_new_int(9));
    queue_pushback(que, cds_new_int(16));

    BOOST_CHECK(queue_isempty(que) == false);
    BOOST_CHECK(queue_length(que) == 3);

    int * pval = (int *) queue_pop(que);
    BOOST_CHECK(*pval == 4);
    BOOST_CHECK(queue_length(que) == 2);
    free(pval);

    queue_free(que);
}

BOOST_AUTO_TEST_SUITE_END()
