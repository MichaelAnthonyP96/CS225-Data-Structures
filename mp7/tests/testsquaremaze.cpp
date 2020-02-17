/**
 * @file testsquaremaze.cpp
 * Performs basic tests of SquareMaze.
 * @date April 2007
 * @author Jonathan Ray
 */

#include "PNG.h"
#include "dsets.h"
#include "maze.h"
#include <iostream>

using namespace std;
using namespace cs225;

int main() {
  SquareMaze m;
  m.makeMaze(100, 100);
  std::cout << "MakeMaze complete" << std::endl;

  PNG *unsolved = m.drawMaze();
  unsolved->writeToFile("unsolved.png");
  delete unsolved;
  std::cout << "drawMaze complete" << std::endl;

  std::vector<int> sol = m.solveMaze();
  std::cout << "solveMaze complete" << std::endl;

  PNG *solved = m.drawMazeWithSolution();
  solved->writeToFile("solved.png");
  delete solved;
  std::cout << "drawMazeWithSolution complete" << std::endl;

  return 0;
}
