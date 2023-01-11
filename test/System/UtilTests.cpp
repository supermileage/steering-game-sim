#include "catch.hpp"

#include "util.h"

using namespace util;

TEST_CASE("UtilTest") {
    SECTION("valueWithinRangeInclusive test") {
        REQUIRE( valueWithinRangeInclusive(40, 20, 40) );
        REQUIRE( valueWithinRangeInclusive(20, 20, 40) );
        REQUIRE_FALSE( valueWithinRangeInclusive(19, 20, 40) );
        REQUIRE_FALSE( valueWithinRangeInclusive(41, 20, 40) );
    }
    SECTION("valueWithinRangeExclusive test") {
        REQUIRE( valueWithinRangeExclusive(39, 20, 40) );
        REQUIRE( valueWithinRangeExclusive(21, 20, 40) );
        REQUIRE_FALSE( valueWithinRangeExclusive(20, 20, 40) );
        REQUIRE_FALSE( valueWithinRangeExclusive(40, 20, 40) );
    }
    SECTION( "computeDistance test" ) {
        REQUIRE( computeDistance(util::Point {0,0},util::Point {0,0}) == 0 );
        REQUIRE( computeDistance(util::Point {0,0},util::Point {1,0}) == 1 );
        REQUIRE( computeDistance(util::Point {0,0},util::Point {0,1}) == 1 );
        REQUIRE( computeDistance(util::Point {0,0},util::Point {-1,0}) == 1 );
        REQUIRE( computeDistance(util::Point {0,0},util::Point {1,1}) == 2 );
        REQUIRE( computeDistance(util::Point {0,0},util::Point {3,4}) == 5 );
        REQUIRE( computeDistance(util::Point {0,0},util::Point {3,4}) == 5 );
        REQUIRE( computeDistance(util::Point {0,0},util::Point {10,10}) == 15 );
    }
}