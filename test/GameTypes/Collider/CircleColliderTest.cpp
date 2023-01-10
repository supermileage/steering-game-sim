#include "catch.hpp"

#include "MockGameObject.h"
#include "CircleCollider.h"

#define CIRCLE_RADIUS 10

TEST_CASE("CircleColliderTest", "[GameTypes][Collider]") {
    MockGameObject obj1;
    MockGameObject obj2;
    CircleCollider circle1(&obj1, CIRCLE_RADIUS);
    CircleCollider circle2(&obj2, CIRCLE_RADIUS);
    util::Point contact;

    SECTION("CircleCollider::hasCollded -- contact point cardinal directions") {
        obj1.setPosition(util::Point { 30, 30 });
        
        // east
        obj2.setPosition(util::Point { 50, 30 });
        REQUIRE(circle1.hasCollidedWith(&circle2, contact) );
        REQUIRE( contact.x == 40);
        REQUIRE( contact.y == 30);

        // west
        obj2.setPosition(util::Point { 10, 30 });
        REQUIRE(circle1.hasCollidedWith(&circle2, contact) );
        REQUIRE( contact.x == 20);
        REQUIRE( contact.y == 30);

        // north
        obj2.setPosition(util::Point { 30, 10 });
        REQUIRE(circle1.hasCollidedWith(&circle2, contact) );
        REQUIRE( contact.x == 30);
        REQUIRE( contact.y == 20);

        // south
        obj2.setPosition(util::Point { 30, 50 });
        REQUIRE(circle1.hasCollidedWith(&circle2, contact) );
        REQUIRE( contact.x == 30);
        REQUIRE( contact.y == 40);
    }
}
