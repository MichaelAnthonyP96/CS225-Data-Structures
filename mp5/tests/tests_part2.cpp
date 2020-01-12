#include "catch.hpp"

#include <algorithm>
#include <vector>

#include "PNG.h"
#include "HSLAPixel.h"
#include "maptiles.h"
#include "mosaiccanvas.h"

using namespace cs225;


TEST_CASE("Creates a basic MosaicCanvas (gridtest)", "[weight=5][part=2]") {
  // Read `tests/gridtest.png` from disk
  PNG sourcePNG;
  sourcePNG.readFromFile("Images/gridtest.png");
  SourceImage source(sourcePNG, 8);

  // Create a list of images to choose from to make our mosaic.  As a basic
  // test, we'll use images of one pixel colored either red, green, or blue.
  vector<TileImage> tileList;

  PNG a(1, 1);  a.getPixel(0, 0) = HSLAPixel(0, 1, 0.5);   // red
  PNG b(1, 1);  b.getPixel(0, 0) = HSLAPixel(120, 1, 0.5); // green
  PNG c(1, 1);  c.getPixel(0, 0) = HSLAPixel(240, 1, 0.5); // blue

  tileList.push_back(TileImage(a));
  tileList.push_back(TileImage(b));
  tileList.push_back(TileImage(c));

  // Draw the mosaic!
  MosaicCanvas* canvas = mapTiles(source, tileList);
  REQUIRE( canvas != NULL );

  PNG actual = canvas->drawMosaic(10);
  PNG expected;  expected.readFromFile("Images/gridtest-expected.png");

  // Save and check for correctness
  actual.writeToFile("testResults/gridtest-actual.png");
  INFO("Saved `actual` as gridtest-actual.png.");

  REQUIRE( actual == expected );
  delete canvas; canvas = NULL;
}
