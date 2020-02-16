#ifndef SolidColorPicker_H
#define SolidColorPicker_H

#include "Point.h"
#include "HSLAPixel.h"
#include "ColorPicker.h"

using namespace cs225;

/**
 * A color picker class using solid color picking algorithm
 */
class SolidColorPicker : public ColorPicker {
public:
  SolidColorPicker(HSLAPixel color);
  HSLAPixel getColor(unsigned x, unsigned y);

private:
  HSLAPixel color;
};

#endif
