/**
 * @file DFS.h
 */

#ifndef DFS_H
#define DFS_H

#include <cmath>
#include <iterator>
#include <list>
#include <stack>

#include "Point.h"
#include "PNG.h"

#include "ImageTraversal.h"

using namespace cs225;

/**
 * A depth-first ImageTraversal.
 * Derived from base class ImageTraversal
 */
class DFS : public ImageTraversal {
public:
  DFS(const PNG &png, const Point &start, double tolerance);
  ~DFS();

  ImageTraversal::Iterator begin();
  ImageTraversal::Iterator end();

  void add(const Point &point);
  Point pop();
  Point peek() const;
  bool empty() const;
  bool eligible(unsigned x, unsigned y) const;

private:
  /** @todo [Part 1] */
  /** add private members here*/
  PNG image;
  Point start;
  HSLAPixel startPixel;
  double tolerance;
  bool **visited;
  std::stack<Point> s;
};

#endif
