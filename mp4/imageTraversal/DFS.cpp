#include <iterator>
#include <cmath>
#include <list>
#include <iostream>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"

/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this DFS is going to traverse
 * @param start The start point of this DFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this DFS
 */
DFS::DFS(const PNG & png, const Point & start, double tolerance) : image(png), start(start), tolerance(tolerance) {
  /** @todo [Part 1]
	*create a 2D array of booleans of size equal to the image  to
	*keep track of the pixels visited
	*/
	visited = new bool* [image.width()];
	for(unsigned i = 0; i < image.width(); ++i){
		visited[i] = new bool[png.height()];
    for(unsigned j = 0; j < png.height(); ++j){
        visited[i][j] = false;
    }
	}
	//initialize the start pixel as the pixel at the start location in the image
	startPixel = png.getPixel(start.x,start.y);
	//the start pixel has been visited
	visited[start.x][start.y] = true;
	//add(start);
}

//custom destructor to delete the 2D boolean array on the heap
DFS::~DFS(){
	for(unsigned i = 0; i < image.width(); ++i) {
		delete visited[i];
		visited[i] = NULL;
	}
	visited = NULL;
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin() {
  /** @todo [Part 1] */
	//if eligible, add the point to the right
	if(eligible(start.x+1,start.y)){
		Point pt = Point(start.x+1,start.y);
		add(pt);
			}
	//if eligible, add the point below
	if(eligible(start.x,start.y+1)){
		Point pt = Point(start.x,start.y+1);
		add(pt);
	}
	//if eligible, add the point to the left
	if(eligible(start.x-1,start.y)){
		Point pt = Point(start.x-1,start.y);
		add(pt);
	}
	//if eligible, add the point to above
	if(eligible(start.x,start.y-1)){
		Point pt = Point(start.x,start.y-1);
		add(pt);
	}
	//uses the DFS start point to initialize the iterator
  ImageTraversal::Iterator it(*this,start);
  return it;
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point & point) {
  /** @todo [Part 1]
	//pushes the point reference to the DFS stack*/
	s.push(point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() {
  /** @todo [Part 1] */
	//peek at the next value in the stack
	Point p = s.top();
	//while the stack is not empty and the top of the stack has been visited before,
	//pop off all elements until one hasnt been visited or the stack is empty.
	while(!s.empty() && visited[p.x][p.y] == true){
			s.pop();
			if(!s.empty())p = s.top();
	}
	//if the stack is empty return an arbitrary point, when the != operator is invoked
	//it will see that the stack is empty and terminate the process
	if(s.empty()) return Point(0,0);
	//mark the new point as visited
	visited[p.x][p.y] = true;
	//pops off the new value
	s.pop();
  return p;
}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() const {
  /** @todo [Part 1] */
  return s.top();
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
  /** @todo [Part 1] */
  if(s.empty()) return true;
  else return false;
}

bool DFS::eligible(unsigned x, unsigned y)const {
	if( (x  < image.width()) && (y < image.height()) ){
		if(visited[x][y] != true){
			HSLAPixel& pix = image.getPixel(x,y);
			if(calculateDelta(pix, startPixel ) <  tolerance){
				return true;
			}
		}
	}
	return false;
}
