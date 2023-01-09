#include "CollisionHandler.h"
#include "util.h"

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
    if (collider1->hasCollidedWith(collider2)) {
        GameObject::Collision collision(collider1->getOwner(), collider2->getOwner());
        _collisionDelegate->execute((CommandArgs)&collision);
    }
}

bool CollisionHandler::haveCollided(CircleCollider* circle, RectangleCollider* rectangle) {
    util::Point p1 = rectangle->getPosition();
    util::Point p2 = circle->getPosition();
    int32_t distance = util::computeDistance(circle->getPosition(), rectangle->getPosition());

    return util::computeDistance(circle->getPosition(), rectangle->getPosition()) <=
        circle->getRadius() + rectangle->getWidth() / 2;
}

bool CollisionHandler::haveCollided(CircleCollider* circle1, CircleCollider* circle2) {
    return util::computeDistance(circle1->getPosition(), circle2->getPosition()) <=
        circle1->getRadius() + circle2->getRadius();
}

bool CollisionHandler::haveCollided(RectangleCollider* rectangle1, RectangleCollider* rectangle2) {
    return false;
}
