#include "Circle.h"

Circle::Circle(std::string name, bool enableCollisions) : Graphic(name, enableCollisions) { }

// PORTING: Use original implementation in hardware
void Circle::init(SPI_TFT_ILI9341* tft, int32_t xpos, int32_t ypos, int32_t colour, int32_t radius, bool fill) {
	Shape::init(tft, xpos, ypos, colour);
	_radius = radius;
	_fill = fill;
	_tft->registerShape(_id, VirtualDisplayTFT::Circle);
}

// PORTING: Use original implementation in hardware
void Circle::draw() {
	if (_fill)
		_tft->fillcircle(_x, _y, _radius, _colour, _id);
	else
		_tft->circle(_x, _y, _radius, _colour, _id);
}

// PORTING: Use original implementation in hardware
void Circle::clear() {
	
}

void Circle::setRadius(int32_t r) {
	_radius = r;
}

int32_t Circle::getRadius() {
	return _radius;
}

int32_t Circle::getFarthestPixelDistance() {
	return _radius;
}

bool Circle::_hasCollidedWith(Graphic* graphic) {
	return false;
}