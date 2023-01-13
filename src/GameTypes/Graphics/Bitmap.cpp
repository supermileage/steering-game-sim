#include "Bitmap.h"
#include "RectangleCollider.h"

Bitmap::Bitmap(std::string name, bool enableCollisions) : GameObject(name, enableCollisions) { }

void Bitmap::init(SPI_TFT_ILI9341* tft, int32_t xpos, int32_t ypos, int32_t width, int32_t height, unsigned char* bitmap) {
	Shape::init(tft, xpos, ypos, 0);
	_width = width;
	_height = height;
	_bitmap = bitmap;

	_tft->registerShape(_id, VirtualDisplayTFT::BitmapData);  // PORTING: remove this line

	if (_enableCollisions) {
		_collider = new RectangleCollider(this, width, height);
	}
}

void Bitmap::draw() {
	// _tft->Bitmap(_x, _y, _width, _height, _bitmap); // PORTING: uncomment this line
	_tft->Bitmap(_x, _y, _width, _height, _bitmap, _id);
}

void Bitmap::clear() {
	// _tft->fillrect(_x, _y, _x + _width, _y + _height, _background); // PORTING: uncomment this line
}