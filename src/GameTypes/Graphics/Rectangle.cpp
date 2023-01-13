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

		// PORTING: uncomment these lines
		// if (_fill)
		// 	_tft->fillrect(x, y, x + _width, y + _height, _background); 
		// else
		// 	_tft->rect(x, y, x + _width, y + _height, _background); // PORTING: uncomment this line

		_rendered = false;
	}
}

bool Rectangle::move(int64_t t) {
	float deltaX = _speed * ((float)t / MILLI) * _direction.x + _lastDeltaX;
    float deltaY = _speed * ((float)t / MILLI) * _direction.y + _lastDeltaY;
    float roundedX = (deltaX >= 0) ? floor(deltaX) : ceil(deltaX);
    float roundedY = (deltaY >= 0) ? floor(deltaY) : ceil(deltaY);

    _lastDeltaX = (roundedX == 0.0f ? deltaX : 0);
    _lastDeltaY = (roundedY == 0.0f ? deltaY : 0);
    _x += roundedX;
    _y += roundedY;
	_x2 += roundedX;
    _y2 += roundedY;
    
    if (roundedX != 0 || roundedY != 0) {
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
