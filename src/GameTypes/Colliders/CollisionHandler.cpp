#include "CollisionHandler.h"

CollisionHandler* CollisionHandler::_instance = nullptr;

CollisionHandler::CollisionHandler() { }

CollisionHandler& CollisionHandler::instance() {
    if (!_instance) {
        _instance = new CollisionHandler();
    }
    return *_instance;
}

void CollisionHandler::registerCollisionDelegate(util::Command* delegate) {
    _collisionDelegate = delegate;
}

void CollisionHandler::checkCollisions() {
    if (!_collisionDelegate) {
        return;
    }

    const std::vector<Collider*>& allColliders = Collider::allColliders();
    for (int i = 0; i < allColliders.size() - 1; i++) {
        for (int j = i + 1; j < allColliders.size(); j++) {
            _checkCollision(allColliders[i], allColliders[j]);
        }

        if (i == allColliders.size() - 2) {
            break;
        }
    }
}

void CollisionHandler::_checkCollision(Collider* collider1, Collider* collider2) {
	util::Point contact;
    if (collider1->hasCollidedWith(collider2, contact)) {
        Collider::Collision collision(collider1->getOwner(), collider2->getOwner(), contact);
        _collisionDelegate->execute((CommandArgs)&collision);
    }
}

bool CollisionHandler::haveCollided(CircleCollider* circle, RectangleCollider* rectangle, util::Point& contact) {
    util::Point corner1 = rectangle->getPosition();
    util::Point corner2 = util::Point {corner1.x + rectangle->getWidth(), corner1.y + rectangle->getHeight()};
    util::Point topLeft;
    util::Point bottomRight;
    topLeft.x = (corner1.x < corner2.x ? corner1.x : corner2.x);
    bottomRight.x = (corner1.x > corner2.x ? corner1.x : corner2.x);
    topLeft.y = (corner1.y < corner2.y ? corner1.y : corner2.y);
    bottomRight.y = (corner1.y > corner2.y ? corner1.y : corner2.y);

    if (circle->getPosition().x >= topLeft.x - circle->getRadius() &&
		circle->getPosition().x <= bottomRight.x + circle->getRadius()) {
        // side collision
        if (circle->getPosition().y >= topLeft.y && circle->getPosition().y <= bottomRight.y) {
			return true;
		}
    }

    if (circle->getPosition().y >= topLeft.y - circle->getRadius() &&
		circle->getPosition().y <= bottomRight.y + circle->getRadius()) {
        // top/bottom collision
        return circle->getPosition().x >= topLeft.x &&
            circle->getPosition().x <= bottomRight.x;
    }

    return false;
}

bool CollisionHandler::haveCollided(CircleCollider* circle1, CircleCollider* circle2, util::Point& contact) {
    return util::computeDistance(circle1->getPosition(), circle2->getPosition()) <=
        circle1->getRadius() + circle2->getRadius();
}

bool CollisionHandler::haveCollided(RectangleCollider* rectangle1, RectangleCollider* rectangle2, util::Point& contact) {
    return false;
}
