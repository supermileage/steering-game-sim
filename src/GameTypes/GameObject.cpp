#include "GameObject.h"
#include <math.h>

int GameObject::id = 0;
std::vector<GameObject*> GameObject::_allGameObjects;

GameObject::GameObject(std::string name, bool enableCollisions) : _name(name), _enableCollisions(enableCollisions) {
    _id = id++;
    _allGameObjects.push_back(this); // PORTING: remove this line
}

GameObject::~GameObject() {
    if (_collider) {
        delete _collider;
    }
    _allGameObjects.erase(std::remove(_allGameObjects.begin(), _allGameObjects.end(), this), _allGameObjects.end()); // PORTING: remove this line
}

void GameObject::setDirection(Vec2 dir) {
	_direction = dir;
}

Vec2 GameObject::getDirection() {
	return _direction;
}

void GameObject::setSpeed(int32_t speed) {
	_speed = speed;
}

int32_t GameObject::getSpeed() {
	return _speed;
}

void GameObject::setPosition(Point pos) {
    _x = pos.x;
    _y = pos.y;
}

Point GameObject::getPosition() {
    return Point { _x, _y };
}

void GameObject::setCollider(Collider* collider) {
    if (!_collider) {
        if (collider) {
            _enableCollisions = true;
        }
    } else {
        delete collider;
        if (!collider) {
            _enableCollisions = false;
        }
    }
    _collider = collider;
}

const std::string& GameObject::getName() {
    return _name;
}

bool GameObject::move() {
    float deltaX = _speed * _direction.x + _lastDeltaX;
    float deltaY = _speed * _direction.y + _lastDeltaY;
    float roundedX = round(deltaX);
    float roundedY = round(deltaY);

    _lastDeltaX = (roundedX == 0.0f ? deltaX : 0);
    _lastDeltaY = (roundedY == 0.0f ? deltaY : 0);
    _x += roundedX;
    _y += roundedY;
    
    if (roundedX != 0 || roundedY != 0) {
        return true;
    }
    return false;
}

/* Static methods */
void GameObject::drawAll() {
    for (GameObject* graphic : _allGameObjects) {
        graphic->draw();
    }
}