#include "catch.hpp"

#include "util.h"

using namespace util;

TEST_CASE("UtilTest") {
    SECTION("valueWithinRangeInclusive Test") {
        REQUIRE( valueWithinRangeInclusive(40, 20, 40) );
        REQUIRE( valueWithinRangeInclusive(20, 20, 40) );
        REQUIRE_FALSE( valueWithinRangeInclusive(19, 20, 40) );
        REQUIRE_FALSE( valueWithinRangeInclusive(41, 20, 40) );
    }
    SECTION("valueWithinRangeExclusive Test") {
        REQUIRE( valueWithinRangeExclusive(39, 20, 40) );
        REQUIRE( valueWithinRangeExclusive(21, 20, 40) );
        REQUIRE_FALSE( valueWithinRangeExclusive(20, 20, 40) );
        REQUIRE_FALSE( valueWithinRangeExclusive(40, 20, 40) );
    }
}