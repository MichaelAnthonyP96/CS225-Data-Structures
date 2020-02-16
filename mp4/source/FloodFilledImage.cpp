#include "PNG.h"
#include <iostream>
#include <list>

#include "ColorPicker.h"
#include "ImageTraversal.h"

#include "Animation.h"
#include "FloodFilledImage.h"
#include "Point.h"

using namespace cs225;

/**
 * Constructs a new instance of a FloodFilledImage with a image `png`.
 *
 * @param png The starting image of a FloodFilledImage
 */
FloodFilledImage::FloodFilledImage(const PNG &png) : png(png) {
  /** @todo [Part 2] */
}

/**
 * Adds a flood fill operation to the FloodFillImage.  This function must store
 * the operation, which will be used by `animate`.
 *
 * @param traversal ImageTraversal used for this FloodFill operation.
 * @param colorPicker ColorPicker used for this FloodFill operation.
 */
void FloodFilledImage::addFloodFill(ImageTraversal &traversal,
                                    ColorPicker &colorPicker) {
  /** @todo [Part 2] */
  imagTrav_.push_back(&traversal);
  colPick_.push_back(&colorPicker);
}

/**
 * Creates an Animation of frames from the FloodFill operations added to this
 * object.
 *
 * Each FloodFill operation added by `addFloodFill` is executed based on the
 * order the operation was added.  This is done by:
 * 1. Visiting pixels within the image based on the order provided by the
 * ImageTraversal iterator and
 * 2. Updating each pixel to a new color based on the ColorPicker
 *
 * While applying the FloodFill to the image, an Animation is created by saving
 * the image after every `frameInterval` pixels are filled.  To ensure a smooth
 * Animation, the first frame is always the starting image and the final frame
 * is always the finished image.
 *
 * (For example, if `frameInterval` is `4` the frames are:
 *   - The initial frame
 *   - Then after the 4th pixel has been filled
 *   - Then after the 8th pixel has been filled
 *   - ...
 *   - The final frame, after all pixels have been filed)
 */
Animation FloodFilledImage::animate(unsigned frameInterval) const {
  Animation animation;
  /** @todo [Part 2] */
  // adds the first frame to the Animation
  animation.addFrame(png);
  // a for loop to iterator over all imageTraversals and Colorpickers, the index
  // is the same for both
  for (unsigned i = 0; i < imagTrav_.size(); ++i) {
    // iterate over all pixels in the image according to the current iterator
    unsigned frameCount = frameInterval;
    for (ImageTraversal::Iterator itI = imagTrav_[i]->begin();
         itI != imagTrav_[i]->end(); ++itI) {
      --frameCount;
      // get the current Point
      Point p = *itI;
      // get the HSLAPixel at the Point we are currently at
      HSLAPixel &pix = png.getPixel(p.x, p.y);
      // update the color of that Point according to the current ColorPicker
      pix = colPick_[i]->getColor(p.x, p.y);
      if (frameCount == 0) {
        // add a frame after a the desired number of changes
        animation.addFrame(png);
        // reset the frameCount
        frameCount = frameInterval;
      }
    }
  }
  // add the last frame
  animation.addFrame(png);
  return animation;
}
