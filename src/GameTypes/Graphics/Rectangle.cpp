#include "Rectangle.h"
#include "RectangleCollider.h"

Rectangle::Rectangle(std::string name, bool enableCollisions) : GameObject(name, enableCollisions) { }

void Rectangle::init(SPI_TFT_ILI9341* tft, int32_t xpos1, int32_t ypos1, int32_t colour, int32_t xpos2, int32_t ypos2, bool fill) {
	Shape::init(tft, xpos1, ypos1, colour);
	_x2 = xpos2;
	_y2 = ypos2;
	_width = xpos2 - xpos1;
	_height = ypos2 - ypos1;
	_center.x = xpos1 + _width / 2;
	_center.y = ypos1 + _height / 2;
	_fill = fill;
	
	_tft->registerShape(_id, VirtualDisplayTFT::Rectangle);  // PORTING: remove this line

	if (_enableCollisions) {
		_collider = new RectangleCollider(this, xpos2 - xpos1, ypos2 - ypos1);
	}
}

void Rectangle::init(SPI_TFT_ILI9341* tft, util::Point center, int32_t width, int32_t height, int32_t colour, bool fill) {
	init(tft, center.x-width/2, center.y-height/2, colour, center.x+width/2, center.y+height/2, fill);
	_center = center;
}

// PORTING: Use original implementation in hardware
void Rectangle::draw() {
	if (_fill)
		_tft->fillrect(_x, _y, _x2, _y2, _colour, _id);
	else
		_tft->rect(_x, _y, _x2, _y2, _colour, _id);
}

// PORTING: Use original implementation in hardware
void Rectangle::clear() {
	// _tft->fillrect(_x, _y, _x2, _y2, _background);
}

bool Rectangle::move() {
	float deltaX = _speed * _direction.x + _lastDeltaX;
    float deltaY = _speed * _direction.y + _lastDeltaY;
    float roundedX = round(deltaX);
    float roundedY = round(deltaY);

    _lastDeltaX = (roundedX == 0.0f ? deltaX : 0);
    _lastDeltaY = (roundedY == 0.0f ? deltaY : 0);
    _center.x += roundedX;
    _center.y += roundedY;
    
    if (roundedX != 0 || roundedY != 0) {
		_x = _center.x - _width / 2;
		_y = _center.y - _height / 2;
		_x2 = _center.x + _width / 2;
		_y2 = _center.y + _height / 2;
        return true;
    }
    return false;
}

void Rectangle::setPosition(util::Point pos) {
	_center = pos;
}

Point Rectangle::getPosition() {
	return _center;
}
