#include "catch.hpp"

#include "MockGameObject.h"
#include "RectangleCollider.h"

#define RECTANGLE_WIDTH 20
#define RECTANGLE_HEIGHT 20
#define CIRCLE_RADIUS 10

TEST_CASE("RectangleColliderTest", "[GameTypes][Collider]") {
	MockGameObject obj;
	RectangleCollider rectangle(&obj, RECTANGLE_WIDTH, RECTANGLE_HEIGHT);
	SECTION( "detect left-side collision with Circle" ) {
		MockGameObject circleObj;
		CircleCollider circle(&circleObj, 10);

		obj.setPosition(util::Point { 20, 20 });

		// test center
		circleObj.setPosition(util::Point { 9, 30 });
		REQUIRE_FALSE( rectangle.hasCollidedWith(&circle) );

		circleObj.setPosition(util::Point { 10, 30 });
		REQUIRE( rectangle.hasCollidedWith(&circle) );

		circleObj.setPosition(util::Point { 11, 30 });
		REQUIRE( rectangle.hasCollidedWith(&circle) );

		// test upper-left corner
		circleObj.setPosition(util::Point { 9, 20 });
		REQUIRE_FALSE( rectangle.hasCollidedWith(&circle) );

		circleObj.setPosition(util::Point { 10, 20 });
		REQUIRE( rectangle.hasCollidedWith(&circle) );

		circleObj.setPosition(util::Point { 11, 20 });
		REQUIRE( rectangle.hasCollidedWith(&circle) );

		// test lower-left corner
		circleObj.setPosition(util::Point { 9, 40 });
		REQUIRE_FALSE( rectangle.hasCollidedWith(&circle) );

		circleObj.setPosition(util::Point { 10, 40 });
		REQUIRE( rectangle.hasCollidedWith(&circle) );

		circleObj.setPosition(util::Point { 11, 40 });
		REQUIRE( rectangle.hasCollidedWith(&circle) );

		// test corner edge cases
		circleObj.setPosition(util::Point { 10, 19 });
		bool result = rectangle.hasCollidedWith(&circle);
		REQUIRE_FALSE( result );

		circleObj.setPosition(util::Point { 10, 41 });
		REQUIRE_FALSE( rectangle.hasCollidedWith(&circle) );
	}

	SECTION( "detect right-side collision with Circle" ) {
		MockGameObject circleObj;
		CircleCollider circle(&circleObj, 10);

		obj.setPosition(util::Point { 20, 20 });

		// test center
		circleObj.setPosition(util::Point { 51, 30 });
		REQUIRE_FALSE( rectangle.hasCollidedWith(&circle) );

		circleObj.setPosition(util::Point { 50, 30 });
		REQUIRE( rectangle.hasCollidedWith(&circle) );

		circleObj.setPosition(util::Point { 49, 30 });
		REQUIRE( rectangle.hasCollidedWith(&circle) );

		// test upper-right corner
		circleObj.setPosition(util::Point { 51, 20 });
		REQUIRE_FALSE( rectangle.hasCollidedWith(&circle) );

		circleObj.setPosition(util::Point { 50, 20 });
		REQUIRE( rectangle.hasCollidedWith(&circle) );

		circleObj.setPosition(util::Point { 49, 20 });
		REQUIRE( rectangle.hasCollidedWith(&circle) );

		// test lower-right corner
		circleObj.setPosition(util::Point { 51, 40 });
		REQUIRE_FALSE( rectangle.hasCollidedWith(&circle) );

		circleObj.setPosition(util::Point { 50, 40 });
		REQUIRE( rectangle.hasCollidedWith(&circle) );

		circleObj.setPosition(util::Point { 49, 40 });
		REQUIRE( rectangle.hasCollidedWith(&circle) );

		// test corner edge cases
		circleObj.setPosition(util::Point { 50, 19 });
		REQUIRE_FALSE( rectangle.hasCollidedWith(&circle) );

		circleObj.setPosition(util::Point { 50, 41 });
		REQUIRE_FALSE( rectangle.hasCollidedWith(&circle) );
	}

	SECTION( "detect top-side collision with Circle" ) {
		MockGameObject circleObj;
		CircleCollider circle(&circleObj, 10);

		obj.setPosition(util::Point { 20, 20 });

		// test center
		circleObj.setPosition(util::Point { 30, 9 });
		REQUIRE_FALSE( rectangle.hasCollidedWith(&circle) );

		circleObj.setPosition(util::Point { 30, 10 });
		REQUIRE( rectangle.hasCollidedWith(&circle) );

		circleObj.setPosition(util::Point { 30, 11 });
		REQUIRE( rectangle.hasCollidedWith(&circle) );

		// test upper-left corner
		circleObj.setPosition(util::Point { 20, 9 });
		REQUIRE_FALSE( rectangle.hasCollidedWith(&circle) );

		circleObj.setPosition(util::Point { 20, 10 });
		REQUIRE( rectangle.hasCollidedWith(&circle) );

		circleObj.setPosition(util::Point { 20, 11 });
		REQUIRE( rectangle.hasCollidedWith(&circle) );

		// test upper-right corner
		circleObj.setPosition(util::Point { 40, 9 });
		REQUIRE_FALSE( rectangle.hasCollidedWith(&circle) );

		circleObj.setPosition(util::Point { 40, 10 });
		REQUIRE( rectangle.hasCollidedWith(&circle) );

		circleObj.setPosition(util::Point { 40, 11 });
		REQUIRE( rectangle.hasCollidedWith(&circle) );

		// test corner edge cases
		circleObj.setPosition(util::Point { 19, 10 });
		REQUIRE_FALSE( rectangle.hasCollidedWith(&circle) );

		// test lower-left corner
		circleObj.setPosition(util::Point { 41, 10 });
		REQUIRE_FALSE( rectangle.hasCollidedWith(&circle) );
	}

}