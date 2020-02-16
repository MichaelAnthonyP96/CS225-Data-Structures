/**
 * @file BFS.h
 */

#ifndef BFS_H
#define BFS_H

#include <cmath>
#include <iterator>
#include <list>
#include <queue>

#include "Point.h"
#include "PNG.h"

#include "ImageTraversal.h"

using namespace cs225;

/**
 * A breadth-first ImageTraversal.
 * Derived from base class ImageTraversal
 */
class BFS : public ImageTraversal {
public:
  BFS(const PNG &png, const Point &start, double tolerance);
  ~BFS();

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
  std::queue<Point> q;
};

#endif
