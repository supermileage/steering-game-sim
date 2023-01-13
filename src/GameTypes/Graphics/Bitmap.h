#ifndef _BITMAP_H_
#define _BITMAP_H_

#include "GameObject.h"

class Bitmap : public GameObject {
	public:
		Bitmap(std::string name = "", bool enableCollisions = false);
		~Bitmap() { }
		void init(SPI_TFT_ILI9341* tft, int32_t xpos, int32_t ypos, int32_t width, int32_t height, unsigned char* bitmap);
		void draw() override;
		void clear() override;
	
	private:
		int32_t _width;
		int32_t _height;
		unsigned char* _bitmap;
};

#endif