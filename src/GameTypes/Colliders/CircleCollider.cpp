#include "CircleCollider.h"

CircleCollider::CircleCollider(GameObject* owner, int32_t radius) :
    Collider(owner), _radius(radius) {
    _type = Circle;
}

void CircleCollider::setRadius(int32_t r) {
    _radius = r;
}

int32_t CircleCollider::getRadius() {
    return _radius;
}

bool CircleCollider::_hasCollidedWith(Collider* collider) {
    switch (collider->getType()) {
        case Circle:
            return CollisionHandler::haveCollided((CircleCollider*)collider, this);
            break;
        case Rectangle:
            return CollisionHandler::haveCollided(this, (RectangleCollider*)collider);
            break;
        default:
            break;
    }
}

int32_t CircleCollider::getFarthestCollisionDistance() {
	return _radius;
}