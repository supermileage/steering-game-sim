#include "Graphic.h"
#include <math.h>

int Graphic::id = 0;

Graphic::Graphic() {
    _id = id++;
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

void Graphic::move() {
    float deltaX = _speed * _direction.x + _lastDeltaX;
    float deltaY = _speed * _direction.y + _lastDeltaY;
    float roundedX = round(deltaX);
    float roundedY = round(deltaY);

    _lastDeltaX = (roundedX == 0.0f ? deltaX : 0);
    _lastDeltaY = (roundedY == 0.0f ? deltaY : 0);
    _x += roundedX;
    _y += roundedY;
    
    if (roundedX != 0 || roundedY != 0) {
        clear();
        draw();
    }
}