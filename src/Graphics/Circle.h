#ifndef _CIRCLE_H_
#define _CIRCLE_H_

#include "Graphic.h"

class Circle : public Graphic {
	public:
		~Circle() { }
		void init(SPI_TFT_ILI9341* tft, int32_t xpos, int32_t ypos, int32_t colour, int32_t radius, bool _fill);
		void draw() override;
		void clear() override;
		
	private:
		int32_t _radius;
		bool _fill;
};

#endif