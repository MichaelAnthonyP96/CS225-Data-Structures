#include <iterator>
#include <cmath>
#include <list>
#include <queue>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "BFS.h"

using namespace cs225;

/**
 * Initializes a breadth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this BFS is going to traverse
 * @param start The start point of this BFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this BFS
 */
BFS::BFS(const PNG & png, const Point & start, double tolerance) : image(png), start(start), tolerance(tolerance){
  /** @todo [Part 1] */
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
//IF THE ENTIRE DFS OBJECT IS ON THE HEAP DO I NEED TO IMPLEMENT THE 2D ARRAY ON THE HEAP AS WELL?
BFS::~BFS(){
	 // for(unsigned i= 0; i < image.width(); ++i){
   //    for(unsigned j = 0;j< image.height(); ++j){
   //      delete visited[i][j];
   //      visited[i][j] = NULL;
   //    }
   //  }
   for(unsigned i = 0; i < image.width(); ++i) {
 		delete visited[i];
 		visited[i] = NULL;
 	}
 	visited = NULL;
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator BFS::begin() {
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
  //uses the BFS start point to initialize the iterator
  ImageTraversal::Iterator it(*this,start);
  return it;
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();

}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point & point) {
  /** @todo [Part 1] */
  q.push(point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop() {
  /** @todo [Part 1] */
	//peek at next value in the queue
	Point p = q.front();
	//while the queue is not empty and the front of the queue has been visited before,
	//pop off all elements until one hasnt been visited or the queue is empty.
	while(!q.empty() && visited[p.x][p.y] == true){
			q.pop();
			if(!q.empty()) p = q.front();
	}
	//if the queue is empty return an arbitrary point, when the != operator is invoked
	//it will see that the queue is empty and terminate the process
	if(q.empty()) return Point(0,0);
	//pushs the point to the queue
	visited[p.x][p.y] = true;
	//pops off the new value
	q.pop();
  return p;
}

/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek() const {
  /** @todo [Part 1] */
  return q.front();
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
  /** @todo [Part 1] */
  if(q.empty()) return true;
  else return false;
}

bool BFS::eligible(unsigned x, unsigned y)const {
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
