#include "catch.hpp"

#include "MockGameObject.h"
#include "RectangleCollider.h"

#define RECTANGLE_WIDTH 20
#define RECTANGLE_HEIGHT 20
#define CIRCLE_RADIUS 10

TEST_CASE("RectangleColliderTest", "[GameTypes][Collider]") {
	MockGameObject obj;
	RectangleCollider rectangle(&obj, RECTANGLE_WIDTH, RECTANGLE_HEIGHT);
	util::Point contact;
	SECTION("RectangleCollider::getCenter test") {
		rectangle.setWidth(5);
		rectangle.setHeight(5);
		obj.setPosition(util::Point{0,0});

		REQUIRE( rectangle.getCenter().x == 2 );
		REQUIRE( rectangle.getCenter().y == 2 );

		rectangle.setWidth(20);
		rectangle.setHeight(20);
		REQUIRE( rectangle.getCenter().x == 10 );
		REQUIRE( rectangle.getCenter().y == 10 );
	}

	SECTION("RectangleCollider::hasCollided with circle collider") {
		MockGameObject circleObj;
		CircleCollider circle(&circleObj, 10);

		SECTION( "detect left-side collision with Circle" ) {
			obj.setPosition(util::Point { 20, 20 });

			// test center
			circleObj.setPosition(util::Point { 9, 30 });
			REQUIRE_FALSE( rectangle.hasCollidedWith(&circle, contact) );

			circleObj.setPosition(util::Point { 10, 30 });
			REQUIRE( rectangle.hasCollidedWith(&circle, contact) );
			REQUIRE( contact.x == 20 );
			REQUIRE ( contact.y == 30 );

			circleObj.setPosition(util::Point { 11, 30 });
			REQUIRE( rectangle.hasCollidedWith(&circle, contact) );
			REQUIRE( contact.x == 20 );
			REQUIRE ( contact.y == 30 );

			// test upper-left corner
			circleObj.setPosition(util::Point { 9, 20 });
			REQUIRE_FALSE( rectangle.hasCollidedWith(&circle, contact) );

			circleObj.setPosition(util::Point { 10, 20 });
			REQUIRE( rectangle.hasCollidedWith(&circle, contact) );
			REQUIRE( contact.x == 20 );
			REQUIRE ( contact.y == 20 );

			circleObj.setPosition(util::Point { 11, 20 });
			REQUIRE( rectangle.hasCollidedWith(&circle, contact) );
			REQUIRE( contact.x == 20 );
			REQUIRE ( contact.y == 20 );

			// test lower-left corner
			circleObj.setPosition(util::Point { 9, 40 });
			REQUIRE_FALSE( rectangle.hasCollidedWith(&circle, contact) );

			circleObj.setPosition(util::Point { 10, 40 });
			REQUIRE( rectangle.hasCollidedWith(&circle, contact) );
			REQUIRE( contact.x == 20 );
			REQUIRE ( contact.y == 40 );

			circleObj.setPosition(util::Point { 11, 40 });
			REQUIRE( rectangle.hasCollidedWith(&circle, contact) );
			REQUIRE( contact.x == 20 );
			REQUIRE ( contact.y == 40 );

			// test corner edge cases
			circleObj.setPosition(util::Point { 10, 19 });
			REQUIRE_FALSE( rectangle.hasCollidedWith(&circle, contact) );

			circleObj.setPosition(util::Point { 10, 51 });
			REQUIRE_FALSE( rectangle.hasCollidedWith(&circle, contact) );
		}

		SECTION( "detect right-side collision with Circle" ) {
			MockGameObject circleObj;
			CircleCollider circle(&circleObj, 10);
			util::Point contact;

			obj.setPosition(util::Point { 20, 20 });

			// test center
			circleObj.setPosition(util::Point { 51, 30 });
			REQUIRE_FALSE( rectangle.hasCollidedWith(&circle, contact) );

			circleObj.setPosition(util::Point { 50, 30 });
			REQUIRE( rectangle.hasCollidedWith(&circle, contact) );
			REQUIRE( contact.x == 40 );
			REQUIRE ( contact.y == 30 );

			circleObj.setPosition(util::Point { 49, 30 });
			REQUIRE( rectangle.hasCollidedWith(&circle, contact) );
			REQUIRE( contact.x == 40 );
			REQUIRE ( contact.y == 30 );

			// test upper-right corner
			circleObj.setPosition(util::Point { 51, 20 });
			REQUIRE_FALSE( rectangle.hasCollidedWith(&circle, contact) );

			circleObj.setPosition(util::Point { 50, 20 });
			REQUIRE( rectangle.hasCollidedWith(&circle, contact) );
			REQUIRE( contact.x == 40 );
			REQUIRE ( contact.y == 20 );

			circleObj.setPosition(util::Point { 49, 20 });
			REQUIRE( rectangle.hasCollidedWith(&circle, contact) );
			REQUIRE( contact.x == 40 );
			REQUIRE ( contact.y == 20 );

			// test lower-right corner
			circleObj.setPosition(util::Point { 51, 40 });
			REQUIRE_FALSE( rectangle.hasCollidedWith(&circle, contact) );

			circleObj.setPosition(util::Point { 50, 40 });
			REQUIRE( rectangle.hasCollidedWith(&circle, contact) );
			REQUIRE( contact.x == 40 );
			REQUIRE ( contact.y == 40 );

			circleObj.setPosition(util::Point { 49, 40 });
			REQUIRE( rectangle.hasCollidedWith(&circle, contact) );
			REQUIRE( contact.x == 40 );
			REQUIRE ( contact.y == 40 );

			// test corner edge cases
			circleObj.setPosition(util::Point { 50, 19 });
			REQUIRE_FALSE( rectangle.hasCollidedWith(&circle, contact) );

			circleObj.setPosition(util::Point { 50, 41 });
			REQUIRE_FALSE( rectangle.hasCollidedWith(&circle, contact) );
		}

		SECTION( "detect top-side collision with Circle" ) {
			obj.setPosition(util::Point { 20, 20 });

			// test center
			circleObj.setPosition(util::Point { 30, 9 });
			REQUIRE_FALSE( rectangle.hasCollidedWith(&circle, contact) );

			circleObj.setPosition(util::Point { 30, 10 });
			REQUIRE( rectangle.hasCollidedWith(&circle, contact) );
			REQUIRE( contact.x == 30 );
			REQUIRE ( contact.y == 20 );

			circleObj.setPosition(util::Point { 30, 11 });
			REQUIRE( rectangle.hasCollidedWith(&circle, contact) );
			REQUIRE( contact.x == 30 );
			REQUIRE ( contact.y == 20 );

			// test upper-left corner
			circleObj.setPosition(util::Point { 20, 9 });
			REQUIRE_FALSE( rectangle.hasCollidedWith(&circle, contact) );

			circleObj.setPosition(util::Point { 20, 10 });
			REQUIRE( rectangle.hasCollidedWith(&circle, contact) );
			REQUIRE( contact.x == 20 );
			REQUIRE ( contact.y == 20 );

			circleObj.setPosition(util::Point { 20, 11 });
			REQUIRE( rectangle.hasCollidedWith(&circle, contact) );
			REQUIRE( contact.x == 20 );
			REQUIRE ( contact.y == 20 );

			// test upper-right corner
			circleObj.setPosition(util::Point { 40, 9 });
			REQUIRE_FALSE( rectangle.hasCollidedWith(&circle, contact) );

			circleObj.setPosition(util::Point { 40, 10 });
			REQUIRE( rectangle.hasCollidedWith(&circle, contact) );
			REQUIRE( contact.x == 40 );
			REQUIRE ( contact.y == 20 );

			circleObj.setPosition(util::Point { 40, 11 });
			REQUIRE( rectangle.hasCollidedWith(&circle, contact) );
			REQUIRE( contact.x == 40 );
			REQUIRE ( contact.y == 20 );

			// test corner edge cases
			circleObj.setPosition(util::Point { 9, 10 });
			REQUIRE_FALSE( rectangle.hasCollidedWith(&circle, contact) );

			circleObj.setPosition(util::Point { 41, 10 });
			REQUIRE_FALSE( rectangle.hasCollidedWith(&circle, contact) );
		}
		SECTION( "detect bottom-side collision with Circle" ) {
			obj.setPosition(util::Point { 20, 20 });

			// test center
			circleObj.setPosition(util::Point { 30, 51 });
			REQUIRE_FALSE( rectangle.hasCollidedWith(&circle, contact) );

			circleObj.setPosition(util::Point { 30, 50 });
			REQUIRE( rectangle.hasCollidedWith(&circle, contact) );
			REQUIRE( contact.x == 30 );
			REQUIRE ( contact.y == 40 );

			circleObj.setPosition(util::Point { 30, 49 });
			REQUIRE( rectangle.hasCollidedWith(&circle, contact) );
			REQUIRE( contact.x == 30 );
			REQUIRE ( contact.y == 40 );

			// test bottom-left corner
			circleObj.setPosition(util::Point { 20, 51 });
			REQUIRE_FALSE( rectangle.hasCollidedWith(&circle, contact) );

			circleObj.setPosition(util::Point { 20, 50 });
			REQUIRE( rectangle.hasCollidedWith(&circle, contact) );
			REQUIRE( contact.x == 20 );
			REQUIRE ( contact.y == 40 );

			circleObj.setPosition(util::Point { 20, 49 });
			REQUIRE( rectangle.hasCollidedWith(&circle, contact) );
			REQUIRE( contact.x == 20 );
			REQUIRE ( contact.y == 40 );

			// test bottom-right corner
			circleObj.setPosition(util::Point { 40, 51 });
			REQUIRE_FALSE( rectangle.hasCollidedWith(&circle, contact) );

			circleObj.setPosition(util::Point { 40, 50 });
			REQUIRE( rectangle.hasCollidedWith(&circle, contact) );
			REQUIRE( contact.x == 40 );
			REQUIRE ( contact.y == 40 );

			circleObj.setPosition(util::Point { 40, 49 });
			REQUIRE( rectangle.hasCollidedWith(&circle, contact) );
			REQUIRE( contact.x == 40 );
			REQUIRE ( contact.y == 40 );

			// test corner edge cases
			circleObj.setPosition(util::Point { 9, 50 });
			REQUIRE_FALSE( rectangle.hasCollidedWith(&circle, contact) );

			circleObj.setPosition(util::Point { 41, 50 });
			REQUIRE_FALSE( rectangle.hasCollidedWith(&circle, contact) );
		}
	}
	SECTION("RectangleCollider::hasCollided with rectangle collider") {
		obj.setPosition(util::Point {20, 20});
		MockGameObject rectangleObj;
		util::Point contact;

		SECTION("Left-side collision with smaller rectangle collider") {
			RectangleCollider rectangle2(&rectangleObj, 10, 10);

			// middle
			rectangleObj.setPosition(util::Point {9, 30});
			REQUIRE_FALSE( rectangle.hasCollidedWith(&rectangle2, contact) );

			rectangleObj.setPosition(util::Point {10, 30});
			REQUIRE( rectangle.hasCollidedWith(&rectangle2, contact) );
			REQUIRE( contact.x == 20 );
			REQUIRE( contact.y == 30 );

			rectangleObj.setPosition(util::Point {11, 30});
			REQUIRE( rectangle.hasCollidedWith(&rectangle2, contact) );
			REQUIRE( contact.x == 20 );
			REQUIRE( contact.y == 30 );

			// top corner
			rectangleObj.setPosition(util::Point {9, 20});
			REQUIRE_FALSE( rectangle.hasCollidedWith(&rectangle2, contact) );

			rectangleObj.setPosition(util::Point {10, 20});
			REQUIRE( rectangle.hasCollidedWith(&rectangle2, contact) );
			REQUIRE( contact.x == 20 );
			REQUIRE( contact.y == 20 );

			rectangleObj.setPosition(util::Point {11, 20});
			REQUIRE( rectangle.hasCollidedWith(&rectangle2, contact) );
			REQUIRE( contact.x == 20 );
			REQUIRE( contact.y == 20 );

			// bottom corner
			rectangleObj.setPosition(util::Point {9, 40});
			REQUIRE_FALSE( rectangle.hasCollidedWith(&rectangle2, contact) );

			rectangleObj.setPosition(util::Point {10, 40});
			REQUIRE( rectangle.hasCollidedWith(&rectangle2, contact) );
			REQUIRE( contact.x == 20 );
			REQUIRE( contact.y == 40 );

			rectangleObj.setPosition(util::Point {11, 40});
			REQUIRE( rectangle.hasCollidedWith(&rectangle2, contact) );
			REQUIRE( contact.x == 20 );
			REQUIRE( contact.y == 40 );

			// corner cases
			rectangleObj.setPosition(util::Point {10, 10});
			REQUIRE( rectangle.hasCollidedWith(&rectangle2, contact) );
			REQUIRE( contact.x == 20 );
			REQUIRE( contact.y == 20 );

			rectangleObj.setPosition(util::Point {10, 40});
			REQUIRE( rectangle.hasCollidedWith(&rectangle2, contact) );
			REQUIRE( contact.x == 20 );
			REQUIRE( contact.y == 40 );
		}
		SECTION("Right-side collision with smaller rectangle collider") {
			RectangleCollider rectangle2(&rectangleObj, 10, 10);

			// middle
			rectangleObj.setPosition(util::Point {41, 30});
			REQUIRE_FALSE( rectangle.hasCollidedWith(&rectangle2, contact) );

			rectangleObj.setPosition(util::Point {40, 30});
			REQUIRE( rectangle.hasCollidedWith(&rectangle2, contact) );
			REQUIRE( contact.x == 40 );
			REQUIRE( contact.y == 30 );

			rectangleObj.setPosition(util::Point {39, 30});
			REQUIRE( rectangle.hasCollidedWith(&rectangle2, contact) );
			REQUIRE( contact.x == 40 );
			REQUIRE( contact.y == 30 );

			// top corner
			rectangleObj.setPosition(util::Point {41, 20});
			REQUIRE_FALSE( rectangle.hasCollidedWith(&rectangle2, contact) );

			rectangleObj.setPosition(util::Point {40, 20});
			REQUIRE( rectangle.hasCollidedWith(&rectangle2, contact) );
			REQUIRE( contact.x == 40 );
			REQUIRE( contact.y == 20 );

			rectangleObj.setPosition(util::Point {39, 20});
			REQUIRE( rectangle.hasCollidedWith(&rectangle2, contact) );
			REQUIRE( contact.x == 40 );
			REQUIRE( contact.y == 20 );

			// bottom corner
			rectangleObj.setPosition(util::Point {41, 40});
			REQUIRE_FALSE( rectangle.hasCollidedWith(&rectangle2, contact) );

			rectangleObj.setPosition(util::Point {40, 40});
			REQUIRE( rectangle.hasCollidedWith(&rectangle2, contact) );
			REQUIRE( contact.x == 40 );
			REQUIRE( contact.y == 40 );

			rectangleObj.setPosition(util::Point {39, 40});
			REQUIRE( rectangle.hasCollidedWith(&rectangle2, contact) );
			REQUIRE( contact.x == 39 );
			REQUIRE( contact.y == 40 );
		}
		SECTION("Top-side collision with smaller rectangle collider") {
			RectangleCollider rectangle2(&rectangleObj, 10, 10);

			// middle
			rectangleObj.setPosition(util::Point {30, 9});
			REQUIRE_FALSE( rectangle.hasCollidedWith(&rectangle2, contact) );

			rectangleObj.setPosition(util::Point {30, 10});
			REQUIRE( rectangle.hasCollidedWith(&rectangle2, contact) );
			REQUIRE( contact.x == 30 );
			REQUIRE( contact.y == 20 );

			rectangleObj.setPosition(util::Point {30, 11});
			REQUIRE( rectangle.hasCollidedWith(&rectangle2, contact) );
			REQUIRE( contact.x == 30 );
			REQUIRE( contact.y == 20 );

			// top left corner
			rectangleObj.setPosition(util::Point {10, 9});
			REQUIRE_FALSE( rectangle.hasCollidedWith(&rectangle2, contact) );

			rectangleObj.setPosition(util::Point {10, 10});
			REQUIRE( rectangle.hasCollidedWith(&rectangle2, contact) );
			REQUIRE( contact.x == 20 );
			REQUIRE( contact.y == 20 );

			rectangleObj.setPosition(util::Point {10, 11});
			REQUIRE( rectangle.hasCollidedWith(&rectangle2, contact) );
			REQUIRE( contact.x == 20 );
			REQUIRE( contact.y == 20 );

			// top right corner
			rectangleObj.setPosition(util::Point {40, 9});
			REQUIRE_FALSE( rectangle.hasCollidedWith(&rectangle2, contact) );

			rectangleObj.setPosition(util::Point {40, 10});
			REQUIRE( rectangle.hasCollidedWith(&rectangle2, contact) );
			REQUIRE( contact.x == 40 );
			REQUIRE( contact.y == 20 );

			rectangleObj.setPosition(util::Point {40, 11});
			REQUIRE( rectangle.hasCollidedWith(&rectangle2, contact) );
			REQUIRE( contact.x == 40 );
			REQUIRE( contact.y == 20 );
		}
		SECTION("Bottom-side collision with smaller rectangle collider") {
			RectangleCollider rectangle2(&rectangleObj, 10, 10);

			// middle
			rectangleObj.setPosition(util::Point {30, 41});
			REQUIRE_FALSE( rectangle.hasCollidedWith(&rectangle2, contact) );

			rectangleObj.setPosition(util::Point {30, 40});
			REQUIRE( rectangle.hasCollidedWith(&rectangle2, contact) );
			REQUIRE( contact.x == 30 );
			REQUIRE( contact.y == 40 );

			rectangleObj.setPosition(util::Point {30, 39});
			REQUIRE( rectangle.hasCollidedWith(&rectangle2, contact) );
			REQUIRE( contact.x == 30 );
			REQUIRE( contact.y == 40 );

			// bottom left corner
			rectangleObj.setPosition(util::Point {20, 41});
			REQUIRE_FALSE( rectangle.hasCollidedWith(&rectangle2, contact) );

			rectangleObj.setPosition(util::Point {20, 40});
			REQUIRE( rectangle.hasCollidedWith(&rectangle2, contact) );
			REQUIRE( contact.x == 20 );
			REQUIRE( contact.y == 40 );

			rectangleObj.setPosition(util::Point {20, 39});
			REQUIRE( rectangle.hasCollidedWith(&rectangle2, contact) );
			REQUIRE( contact.x == 20 );
			REQUIRE( contact.y == 40 );

			// bottom right corner
			rectangleObj.setPosition(util::Point {40, 41});
			REQUIRE_FALSE( rectangle.hasCollidedWith(&rectangle2, contact) );

			rectangleObj.setPosition(util::Point {40, 40});
			REQUIRE( rectangle.hasCollidedWith(&rectangle2, contact) );
			REQUIRE( contact.x == 40 );
			REQUIRE( contact.y == 40 );

			rectangleObj.setPosition(util::Point {40, 39});
			REQUIRE( rectangle.hasCollidedWith(&rectangle2, contact) );
			REQUIRE( contact.x == 40 );
			REQUIRE( contact.y == 40 );
		}
	}
}