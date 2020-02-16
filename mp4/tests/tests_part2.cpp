#include "catch.hpp"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "HSLAPixel.h"
#include "PNG.h"

#include "Animation.h"
#include "FloodFilledImage.h"

#include "BFS.h"
#include "DFS.h"

#include "GradientColorPicker.h"
#include "GridColorPicker.h"
#include "MyColorPicker.h"
#include "RainbowColorPicker.h"
#include "SolidColorPicker.h"

using namespace cs225;

TEST_CASE("Illini I - FloodFilledImage, DFS", "[weight=3][part=2]") {
  PNG png;
  png.readFromFile("inputImages/i.png");
  PNG expected;
  expected.readFromFile("inputImages/i-rainbow-dfs.png");
  PNG expected2;
  expected2.readFromFile("inputImages/i-rainbow-dfs-2.png");

  FloodFilledImage image(png);
  DFS dfs(png, Point(40, 40), 0.05);
  RainbowColorPicker rainbow(0.05);
  image.addFloodFill(dfs, rainbow);

  Animation animation = image.animate(1000);

  REQUIRE(animation.frameCount() > 2);
  PNG secondFrame = animation.getFrame(1);
  PNG lastFrame = animation.getFrame(animation.frameCount() - 1);

  secondFrame.writeToFile("Results/i-rainbow-dfs-2.png");
  lastFrame.writeToFile("Results/i-rainbow-dfs.png");
  animation.write("Results/i-rainbow-dfs.gif");
  INFO("Files written to Results/i-rainbow-dfs-* for debugging.");

  REQUIRE(secondFrame == expected2);
  REQUIRE(lastFrame == expected);
}

TEST_CASE("Illini I - FloodFilledImage, BFS", "[weight=3][part=2]") {
  PNG png;
  png.readFromFile("inputImages/i.png");
  PNG expected;
  expected.readFromFile("inputImages/i-rainbow-bfs.png");
  PNG expected2;
  expected2.readFromFile("inputImages/i-rainbow-bfs-2.png");

  FloodFilledImage image(png);
  BFS bfs(png, Point(40, 40), 0.05);
  RainbowColorPicker rainbow(0.05);
  image.addFloodFill(bfs, rainbow);

  Animation animation = image.animate(1000);

  REQUIRE(animation.frameCount() > 2);
  PNG secondFrame = animation.getFrame(1);
  PNG lastFrame = animation.getFrame(animation.frameCount() - 1);

  secondFrame.writeToFile("Results/i-rainbow-bfs-2.png");
  lastFrame.writeToFile("Results/i-rainbow-bfs.png");
  animation.write("Results/i-rainbow-bfs.gif");
  INFO("Files written to Results/i-rainbow-bfs-* for debugging.");

  REQUIRE(secondFrame == expected2);
  REQUIRE(lastFrame == expected);
}

TEST_CASE("Lantern- FloodFilledImage, BFS", "[weight=3][part=2]") {
  PNG png;
  png.readFromFile("inputImages/lantern.png");
  PNG expected;
  expected.readFromFile("inputImages/lantern-rainbow-bfs.png");
  PNG expected2;
  expected2.readFromFile("inputImages/lantern-rainbow-bfs-2.png");

  FloodFilledImage image(png);
  BFS bfs(png, Point(40, 40), 0.5);
  RainbowColorPicker rainbow(0.5);
  image.addFloodFill(bfs, rainbow);

  Animation animation = image.animate(1000);

  REQUIRE(animation.frameCount() > 2);
  PNG secondFrame = animation.getFrame(1);
  PNG lastFrame = animation.getFrame(animation.frameCount() - 1);

  secondFrame.writeToFile("Results/lantern-rainbow-bfs-2.png");
  lastFrame.writeToFile("Results/lantern-rainbow-bfs.png");
  animation.write("Results/lantern-rainbow-bfs.gif");
  INFO("Files written to Results/lantern-rainbow-dfs-* for debugging.");

  REQUIRE(secondFrame == expected2);
  REQUIRE(lastFrame == expected);
}

TEST_CASE("PacMan - FloodFilledImage, DFS", "[weight=3][part=2]") {
  PNG png;
  png.readFromFile("inputImages/pacman.png");
  PNG expected;
  expected.readFromFile("inputImages/pacman-solid-dfs.png");
  PNG expected2;
  expected2.readFromFile("inputImages/pacman-solid-dfs-2.png");

  FloodFilledImage image(png);
  DFS dfs(png, Point(100, 50), 0.2);
  HSLAPixel color(231, 1, 0.5);
  SolidColorPicker solid(color);
  image.addFloodFill(dfs, solid);

  Animation animation = image.animate(1000);

  REQUIRE(animation.frameCount() > 2);
  PNG secondFrame = animation.getFrame(1);
  PNG lastFrame = animation.getFrame(animation.frameCount() - 1);

  secondFrame.writeToFile("Results/pacman-solid-dfs-2.png");
  lastFrame.writeToFile("Results/pacman-solid-dfs.png");
  animation.write("Results/pacman-solid-dfs.gif");
  INFO("Files written to Results/pacman-solid-dfs-* for debugging.");

  REQUIRE(secondFrame == expected2);
  REQUIRE(lastFrame == expected);
}

TEST_CASE("PacMan - FloodFilledImage, BFS", "[weight=3][part=2]") {
  PNG png;
  png.readFromFile("inputImages/pacman.png");
  PNG expected;
  expected.readFromFile("inputImages/pacman-solid-bfs.png");
  PNG expected2;
  expected2.readFromFile("inputImages/pacman-solid-bfs-2.png");

  FloodFilledImage image(png);
  BFS bfs(png, Point(100, 50), 0.2);
  HSLAPixel color(231, 1, 0.5);
  SolidColorPicker solid(color);
  image.addFloodFill(bfs, solid);

  Animation animation = image.animate(1000);

  REQUIRE(animation.frameCount() > 2);
  PNG secondFrame = animation.getFrame(1);
  PNG lastFrame = animation.getFrame(animation.frameCount() - 1);

  secondFrame.writeToFile("Results/pacman-solid-bfs-2.png");
  lastFrame.writeToFile("Results/pacman-solid-bfs.png");
  animation.write("Results/pacman-solid-bfs.gif");
  INFO("Files written to Results/pacman-solid-bfs-* for debugging.");

  REQUIRE(secondFrame == expected2);
  REQUIRE(lastFrame == expected);
}
