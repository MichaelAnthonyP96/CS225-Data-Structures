/* Your code here! */
#ifndef MAZE_H
#define MAZE_H
#include "HSLAPixel.h"
#include "PNG.h"
#include "dsets.h"
#include <vector>

class SquareMaze {
public:
  // No parameter constructor. Creates an empty maze.
  SquareMaze();
  // Destructor
  ~SquareMaze();
  // Makes a new SquareMaze of the given height and width.
  void makeMaze(int width, int height);
  // This uses your representation of the maze to determine whether it is
  // possible
  // to travel in  the given direction from the square at coordinates(x,y).
  bool canTravel(int x, int y, int dir) const;
  // Sets whether or not the specified wall exists.
  void setWall(int x, int y, int dir, bool exists);
  // Solve this SquareMaze.
  std::vector<int> solveMaze();
  // Draws the maze without the solution.
  cs225::PNG *drawMaze() const;
  // This function calls drawMaze, then solveMaze; it modifies the PNG from
  // drawMaze to show the solution vector and the exit.
  cs225::PNG *drawMazeWithSolution();
  // adjusts the maze in a Block I fashion, marks the left and right portions of
  // the I as having bottom and right walls
  void creativeAdjust();
  // draws the maze in the shape of a Block I
  cs225::PNG *drawCreativeMaze();
  // solves the creative Maze
  std::vector<int> solveCreativeMaze();

private:
  struct cell {
    cell();
    bool bottomWall;
    bool rightWall;
    bool visited;
  };
  int h;
  int w;
  int max;
  int endX;
  int endY;
  void traverse(int &x, int &y, int &length);
  void clear();
  cell **maze;
};
#endif
