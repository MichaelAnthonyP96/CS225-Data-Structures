#include "Point.h"
#include "HSLAPixel.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

/**
 * MyColorPicker constructor
 */
MyColorPicker::MyColorPicker(HSLAPixel color) : color(color) {}
/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  return color;
}
