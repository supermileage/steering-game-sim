#ifndef _TEXT_H_
#define _TEXT_H_

#include "GameObject.h"

#include <string>

class Text : public GameObject {
	public:
		Text(std::string name = "");
		~Text() { }
		void init(SPI_TFT_ILI9341* tft, int32_t xpos, int32_t ypos, unsigned char* font, const std::string& defaultString);
		void draw() override;
		void clear() override;
		void setDisplayString(const std::string& value);

	private:
		unsigned char* _font;
		std::string _displayString;
		std::string _defaultString;
};

#endif