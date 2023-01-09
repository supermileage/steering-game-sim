#include "RectangleCollider.h"

RectangleCollider::RectangleCollider(GameObject* owner, int32_t width, int32_t height) :
 Collider(owner), _width(width), _height(height) {
    _type = Rectangle;
    _farthestDistanceFromCenter = util::computeDistance(Point{ 0 , 0 }, util::Point { (_width / 2),  ( _height / 2) });
}

void RectangleCollider::setWidth(int32_t width) {
    _width = width;
}

int32_t RectangleCollider::getWidth() {
    return _width;
}

void RectangleCollider::setHeight(int32_t height) {
    _height = height;
}

int32_t RectangleCollider::getHeight() {
    return _height;
}

int32_t RectangleCollider::getFarthestCollisionDistance() {
    return _farthestDistanceFromCenter;
}

bool RectangleCollider::_hasCollidedWith(Collider* collider) {
    switch (collider->getType()) {
        case Circle:
            return CollisionHandler::haveCollided((CircleCollider*)collider, this);
            break;
        case Rectangle:
            return CollisionHandler::haveCollided((RectangleCollider*)collider, this);
            break;
        default:
            break;
    }
}