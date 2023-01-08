#include "Graphic.h"
#include <math.h>

int Graphic::id = 0;
Graphic::CollidableGraphics Graphic::_collidableGraphics;
std::vector<Graphic*> Graphic::_allGraphics;

Graphic::Graphic(std::string name, bool enableCollisions) : _name(name), _enableCollisions(enableCollisions) {
    _id = id++;
    if (enableCollisions) {
        _collidableGraphics.add(this);
    }
    _allGraphics.push_back(this); // PORTING: remove this line
}

Graphic::~Graphic() {
    if (_enableCollisions) {
        _collidableGraphics.remove(this);
    }
    _allGraphics.erase(std::remove(_allGraphics.begin(), _allGraphics.end(), this), _allGraphics.end()); // PORTING: remove this line
}

void Graphic::setDirection(Vec2 dir) {
	_direction = dir;
}

Vec2 Graphic::getDirection() {
	return _direction;
}

void Graphic::setSpeed(int32_t speed) {
	_speed = speed;
}

int32_t Graphic::getSpeed() {
	return _speed;
}

void Graphic::setPosition(Pos pos) {
    _x = pos.x;
    _y = pos.y;
}

Pos Graphic::getPosition() {
    return Pos { _x, _y };
}

void Graphic::setEnableCollisions(bool enable) {
    if (enable != _enableCollisions) {
        if (enable) {
            _collidableGraphics.add(this);
        } else {
            _collidableGraphics.remove(this);
        }
        _enableCollisions = enable;
    }
}

const std::string& Graphic::getName() {
    return _name;
}

bool Graphic::move() {
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

bool Graphic::hasCollidedWith(Graphic* graphic) {
    if (_withinCollisionRange(graphic)) {
        return _hasCollidedWith(graphic);
    }
    
    return false;
}

bool Graphic::_withinCollisionRange(Graphic* graphic) {
    return util::computeDistance(getPosition(), graphic->getPosition()) <=
        getFarthestPixelDistance() + graphic->getFarthestPixelDistance();
}

void Graphic::checkCollisions() {
    _collidableGraphics.checkCollisions();
}

void Graphic::registerCollisionDelegate(Command* delegate) {
    _collidableGraphics.registerCollisionDelegate(delegate);
}

void Graphic::drawAll() {
    for (Graphic* graphic : _allGraphics) {
        graphic->draw();
    }
}

void Graphic::CollidableGraphics::add(Graphic* graphic) {
    _graphics.push_back(graphic);
}

void Graphic::CollidableGraphics::remove(Graphic* graphic) {
    _graphics.erase(std::remove(_graphics.begin(), _graphics.end(), graphic), _graphics.end());
}

void Graphic::CollidableGraphics::checkCollisions() {
    for (int i = 0; i < _graphics.size() - 1; i++) {
        for (int j = i + 1; j < _graphics.size(); j++) {
            if (_graphics[i]->hasCollidedWith(_graphics[j])) {
                if (_collisionDelegate) {
                    Collision collision(_graphics[i]->getName(), _graphics[j]->getName());
                    _collisionDelegate->execute((CommandArgs)&collision);
                }
            }
        }
        i++;

        if (i == _graphics.size() - 1) {
            break;
        }
    }
}

void Graphic::CollidableGraphics::registerCollisionDelegate(Command* delegate) {
    _collisionDelegate = delegate;
}