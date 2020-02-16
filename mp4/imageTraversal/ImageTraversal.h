/**
 * @file ImageTraversal.h
 */
#ifndef IMAGETRAVERSAL_H
#define IMAGETRAVERSAL_H

#include "Point.h"
#include "HSLAPixel.h"
#include "PNG.h"
#include <iterator>
#include <stack>

using namespace cs225;

/**
 * A base class for traversal algorithms on images.
 *
 * BFS and DFS will inherit from this class
 *
 * Each derived class must maintain an ordering of points on an image,
 * through calls to the virtual member functions `add` and `pop`.
 *
 * A derived class provides a traversal by returning instances of
 * ImageTraversal::Iterator.
 */
class ImageTraversal {
public:
  /**
   * A forward iterator through an ImageTraversal.
   */
  //  PNG image;
  //  bool** visited;
  //  Point start;
  //  double tolerance;
  class Iterator : std::iterator<std::forward_iterator_tag, Point> {
  public:
    Iterator(); // default constructor
    Iterator(ImageTraversal &traversal,
             Point p); // 2-param constructor used for end()
    ~Iterator();       // destructor

    Iterator &operator++();
    Point operator*();
    bool operator!=(const Iterator &other);
    Iterator operator=(const Iterator &other);
    HSLAPixel startPixel;

    /** @todo [Part 1] */
    /** add member functions if neccesary*/

  private:
    /** @todo [Part 1] */
    /** add private members here if neccesary*/
    ImageTraversal *traversal; // either DFS or BFS
    Point current;             // holds the point throughout the iteration
  };

  ~ImageTraversal();

  static double calculateDelta(const HSLAPixel &p1, const HSLAPixel &p2);

  /**
   * The begining of an iterator
   * Virtual function. Derived class need to implement this
   */
  virtual Iterator begin() = 0;

  /**
   * The end of an iterator
   * Virtual function. Derived class need to implement this
   */
  virtual Iterator end() = 0;

  /**
   * Add new point to the traversal
   * Virtual function. Derived class need to implement this
   */
  virtual void add(const Point &t) = 0;
  /**
   * Remove and return the next point of the traversal
   * Virtual function. Derived class need to implement this
   */
  virtual Point pop() = 0;
  /**
   * Return but not remove the next point of the traversal
   * Virtual function. Derived class need to implement this
   */
  virtual Point peek() const = 0;
  /**
   * To see if the traversal has no points left
   * Virtual function. Derived class need to implement this
   */
  virtual bool empty() const = 0;

  virtual bool eligible(unsigned x, unsigned y) const = 0;
};

#endif
