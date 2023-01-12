#include "Rectangle.h"
#include "RectangleCollider.h"

Rectangle::Rectangle(std::string name, bool enableCollisions) : GameObject(name, enableCollisions) { }

void Rectangle::init(SPI_TFT_ILI9341* tft, int32_t x1, int32_t y1, int32_t colour, int32_t x2, int32_t y2, bool fill) {
	Shape::init(tft, x1, y1, colour);
	_x2 = x2;
	_y2 = y2;
	_width = x2 - x1;
	_height = y2 - y1;
	_fill = fill;
	
	_tft->registerShape(_id, VirtualDisplayTFT::Rectangle);  // PORTING: remove this line

	if (_enableCollisions) {
		_collider = new RectangleCollider(this, x2 - x1, y2 - y1);
	}
}

void Rectangle::init(SPI_TFT_ILI9341* tft, util::Point topLeft, int32_t width, int32_t height, int32_t colour, bool fill) {
	init(tft, topLeft.x, topLeft.y, colour, topLeft.x + width, topLeft.y + height, fill);
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
		if (_rendered) {
		int x = _lastRenderPosition.x;
		int y = _lastRenderPosition.y;
		// _tft->fillrect(x, y, x + _width, y + _height, _background); // PORTING: uncomment this line
		_rendered = false;
	}
}

bool Rectangle::move(int64_t t) {
	float deltaX = _speed * ((float)t / DECA) * _direction.x + _lastDeltaX;
    float deltaY = _speed * ((float)t / DECA) * _direction.y + _lastDeltaY;
    float floorX = floor(deltaX);
    float floorY = floor(deltaY);

    _lastDeltaX = (floorX == 0.0f ? deltaX : 0);
    _lastDeltaY = (floorY == 0.0f ? deltaY : 0);
    _x += floorX;
    _y += floorY;
	_x2 += floorX;
    _y2 += floorY;
    
    if (floorX != 0 || floorY != 0) {
        return true;
    }
    return false;
}

int32_t Rectangle::getWidth() {
	return _width;
}

int32_t Rectangle::getHeight() {
	return _height;
}
