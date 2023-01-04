#include "VirtualDisplayTFT.h"

VirtualDisplayTFT::VirtualDisplayTFT(int width, int height) : _width(width), _height(height) { }

int VirtualDisplayTFT::width() {
    return _width;
}

int VirtualDisplayTFT::height() {
    return _height;
}

void VirtualDisplayTFT::pixel(int x, int y, int colour) {

}

void VirtualDisplayTFT::circle(int x, int y, int r, int colour) {

}

void VirtualDisplayTFT::fillcircle(int x, int y, int r, int colour) {

}

void VirtualDisplayTFT::line(int x0, int y0, int x1, int y1, int colour) {

}

void VirtualDisplayTFT::rect(int x0, int y0, int x1, int y1, int colour) {

}

void VirtualDisplayTFT::fillrect(int x0, int y0, int x1, int y1, int colour) {

}

void VirtualDisplayTFT::locate(int x, int y) {

}

void VirtualDisplayTFT::background(uint16_t colour) {
    _background = colour;
}

void VirtualDisplayTFT::cls(void) {

}

int VirtualDisplayTFT::_putc(int value) {
    return 0;
}

void VirtualDisplayTFT::character(int x, int y, int c) {

}

void VirtualDisplayTFT::Bitmap(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned char *bitmap) {

}

void VirtualDisplayTFT::set_font(unsigned char *f) {

}

int VirtualDisplayTFT::printf(const char *format, ...) {
    return 0;
}

void VirtualDisplayTFT::set_orientation(unsigned int o) {

}
