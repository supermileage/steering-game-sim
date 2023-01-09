#include "Collider.h"

std::vector<Collider*> Collider::_allColliders;

Collider::Collider(GameObject* owner) : _owner(owner) {
    _allColliders.push_back(this);
}

Collider::~Collider() {
    _allColliders.erase(std::remove(_allColliders.begin(), _allColliders.end(), this), _allColliders.end());
}

util::Point Collider::getPosition() {
    return _owner->getPosition();
}

GameObject* Collider::getOwner() {
    return _owner;
}

Collider::ColliderType Collider::getType() {
    return _type;
}

bool Collider::hasCollidedWith(Collider* collider) {
    if (_withinCollisionRange(collider)) {
        return _hasCollidedWith(collider);
    }
    return false;
}

bool Collider::_withinCollisionRange(Collider* collider) {
    return util::computeDistance(getPosition(), collider->getPosition()) <=
        getFarthestCollisionDistance() + collider->getFarthestCollisionDistance();
}

/* Static Methods */
const std::vector<Collider*>& Collider::allColliders() {
    return _allColliders;
}