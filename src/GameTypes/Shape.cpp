#include "Shape.h"

Shape::~Shape() { }

void Shape::init(SPI_TFT_ILI9341* tft, int32_t xpos, int32_t ypos, int32_t colour, int32_t background) {
	_tft = tft;
	_x = xpos;
	_y = ypos;
	_colour = colour;
	_background = background;
}

void Shape::setColour(int32_t value) {
	_colour = value;
}

int32_t Shape::getColour() {
	return _colour;
}
