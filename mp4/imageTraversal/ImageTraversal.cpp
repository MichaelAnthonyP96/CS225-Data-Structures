#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() : traversal(NULL) {
  /** @todo [Part 1] */
  //sets the traversal to NULL and current to
}
/**
 * 2-param iterator constructor.
 */
ImageTraversal::Iterator::Iterator(ImageTraversal& traversal, Point p)
:traversal(&traversal), current(p){
  //Constructors the iterator by initializing the current to point p
  //and the traversal pointer to the given traversal reference
}

ImageTraversal::Iterator::~Iterator(){
  //delete the DFS or BFS object on the heap
  //should I dereference this?
}

ImageTraversal::~ImageTraversal(){

}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1]
  *Add Points to the stack or queue in the following order: right,below,left,above
  */
  //pop off the next Point and add its neighbors
  if(!traversal->empty()) current = traversal->pop();
  //To the right of the current Point
  if(traversal->eligible(current.x+1,current.y)){
    const Point* pt = new Point(current.x+1,current.y);
    traversal->add(*pt);
  }
  //below the current Point
  if(traversal->eligible(current.x,current.y+1)){
    const Point* pt = new Point(current.x,current.y+1);
    traversal->add(*pt);
  }
  //left of the current Point
  if(traversal->eligible(current.x-1,current.y)){
    const Point* pt = new Point(current.x-1,current.y);
    traversal->add(*pt);
  }
  //above the current Point
  if(traversal->eligible(current.x,current.y-1)){
    const Point* pt = new Point(current.x,current.y-1);
    traversal->add(*pt);
  }
  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return current;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  bool thisEmpty = false;
  bool otherEmpty = false;

  if (traversal == NULL) { thisEmpty = true; }
  if (other.traversal == NULL) { otherEmpty = true; }

  if (!thisEmpty)  { thisEmpty = traversal->empty(); }
  if (!otherEmpty) { otherEmpty = other.traversal->empty(); }

  if (thisEmpty && otherEmpty) return false; // both empty then the traversals are equal, return false
  else if ((thisEmpty)||(otherEmpty)) return (true); //both not empty then compare the traversals
  else return true;
}
