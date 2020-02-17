#include "PNG.h"
#include "dsets.h"
#include "maze.h"
#include <iostream>

using namespace std;
using namespace cs225;

int main() {
  // Write your own main here
  SquareMaze m;
  m.makeMaze(100, 100);
  std::cout << "My creative MakeMaze complete" << std::endl;

  m.creativeAdjust();
  std::cout << "My creativeAdjust function has run" << std::endl;

  PNG *unsolved = m.drawCreativeMaze();
  unsolved->writeToFile("Creative.png");
  delete unsolved;
  std::cout << "My creative drawMaze complete" << std::endl;

  std::vector<int> sol = m.solveCreativeMaze();
  std::cout << "My creative solveMaze complete" << std::endl;

  PNG *solved = m.drawMazeWithSolution();
  solved->writeToFile("solvedCreative.png");
  delete solved;
  std::cout << "My creative drawMazeWithSolution complete" << std::endl;

  return 0;
}
