
#include "Animation.h"
#include "FloodFilledImage.h"
#include "PNG.h"

#include "BFS.h"
#include "DFS.h"

#include "GradientColorPicker.h"
#include "GridColorPicker.h"
#include "MyColorPicker.h"
#include "RainbowColorPicker.h"
#include "SolidColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.

  PNG png;
  png.readFromFile("tests/MasterCard.png");

  FloodFilledImage image(png);

  DFS dfs1(png, Point(0, 0), 0.0001);
  MyColorPicker white(HSLAPixel(1, 1, 1, 1));
  image.addFloodFill(dfs1, white);

  DFS dfs2(png, Point(100, 80), 0.0001);
  MyColorPicker orange(HSLAPixel(30, 1, 0.5, 1));
  image.addFloodFill(dfs2, orange);

  BFS bfs(png, Point(200, 80), 0.0001);
  MyColorPicker blue(HSLAPixel(244, 1, 0.3, 1));
  image.addFloodFill(bfs, blue);

  Animation animation = image.animate(500);

  PNG lastFrame = animation.getFrame(animation.frameCount() - 1);
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");

  return 0;
}
