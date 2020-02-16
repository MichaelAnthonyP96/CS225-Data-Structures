/**
 * @file FloodFilledImage.h
 * Definition for a class to do flood fill on an image
 */
#ifndef FLOODFILLEDIMAGE_H
#define FLOODFILLEDIMAGE_H

#include "PNG.h"
#include <iostream>
#include <list>
#include <vector>

#include "ColorPicker.h"
#include "ImageTraversal.h"

#include "Animation.h"
#include "Point.h"

using namespace cs225;
/**
 *This class is used to do flood fill on an image
 */
class FloodFilledImage {
public:
  FloodFilledImage(const PNG &png);
  void addFloodFill(ImageTraversal &traversal, ColorPicker &colorPicker);
  Animation animate(unsigned frameInterval) const;

private:
  /** @todo [Part 2] */
  /** add private members here*/
  PNG png;
  std::vector<ImageTraversal *> imagTrav_;
  std::vector<ColorPicker *> colPick_;
};

#endif
