#include <boost/test/unit_test.hpp>

#include "network/network.hpp"

BOOST_AUTO_TEST_SUITE(network_test)

BOOST_AUTO_TEST_CASE(network_test) {
    BOOST_TEST((get_request("https://ip-api.com")) != "");
}

BOOST_AUTO_TEST_SUITE_END()
