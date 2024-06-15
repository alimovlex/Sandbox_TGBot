#include <boost/test/unit_test.hpp>

#include "exchange_rate/ExchangeRate.hpp"

BOOST_AUTO_TEST_SUITE(course_test)

BOOST_AUTO_TEST_CASE(course_test) {
    ExchangeRate course;
    course.set_currency("USD");
    course.refresh();

    BOOST_TEST(course.get_currency() != 0);
}

BOOST_AUTO_TEST_SUITE_END()
