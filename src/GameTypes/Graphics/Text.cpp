#include "Text.h"

Text::Text(std::string name) : GameObject(name, false) { }

void Text::init(SPI_TFT_ILI9341* tft, int32_t xpos, int32_t ypos, unsigned char* font, const std::string& defaultString) {
	Shape::init(tft, xpos, ypos, WhiteTFT);
	_font = font;
	_displayString = defaultString;
	_defaultString = defaultString;

	_tft->registerShape(_id, VirtualDisplayTFT::Text);  // PORTING: remove this line
}

void Text::draw() {
	// PORTING: uncomment these lines
	// _tft->set_font(_font);
	// _tft->locate(_x, _y);
	// _tft->printf(_displayString.c_str());

	_tft->printf(_displayString, _x, _y, _font, _id); // PORTING: remove this line
}

void Text::setDisplayString(const std::string& value) {
	_displayString = value;
}

void Text::clear() {
	// PORTING: uncomment these lines
	// _tft->set_font(_font);
	// _tft->locate(_x, _y);
	// _tft->printf(_defaultString.c_str());
}