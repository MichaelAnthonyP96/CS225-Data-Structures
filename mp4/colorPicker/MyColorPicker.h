#ifndef MyColorPicker_H
#define MyColorPicker_H

#include "Point.h"
#include "HSLAPixel.h"
#include "ColorPicker.h"

using namespace cs225;

/**
 * A color picker class using your own color picking algorithm
 */
class MyColorPicker : public ColorPicker {
public:
  MyColorPicker(HSLAPixel color);
  HSLAPixel getColor(unsigned x, unsigned y);

private:
  HSLAPixel color;
};

#endif
