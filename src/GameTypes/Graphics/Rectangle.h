#ifndef _RECTANGLE_H_
#define _RECTANGLE_H_

#include "GameObject.h"

class Rectangle : public GameObject {
	public:
		Rectangle(std::string name = "", bool enableCollisions = false);
		~Rectangle() { }
		void init(SPI_TFT_ILI9341* tft, int32_t xpos, int32_t ypos, int32_t colour, int32_t xpos2, int32_t ypos2, bool fill);
		void init(SPI_TFT_ILI9341* tft, Point center, int32_t width, int32_t height, int32_t colour, bool fill);
		void draw() override;
		void clear() override;
		bool move() override;
		void setPosition(util::Point pos) override;
		Point getPosition() override;

	protected:
		int32_t _x2;
		int32_t _y2;
		util::Point _center;
		int32_t _width;
		int32_t _height;
		bool _fill;
};

#endif