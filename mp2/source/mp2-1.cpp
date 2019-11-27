#include <iostream>
#include "include/Image.h"
#include <iostream>

using namespace cs225;

int main() {
  Image alma;

  
  std::cout << "Using Image::darken to create `darken.png`..." << std::endl;
  alma.readFromFile("alma.png");
  alma.darken();
  alma.writeToFile("darken.png");

  
  alma.readFromFile("alma.png");
  std::cout << "Using Image::lighten to create `lighten.png`..." << std::endl;
  alma.lighten(0.2);
  alma.writeToFile("lighten.png");

  std::cout << "Using Image::saturate to create `saturate.png`..." << std::endl;
  alma.readFromFile("alma.png");
  alma.saturate(0.2);
  alma.writeToFile("saturate.png");

  
  std::cout << "Using Image::scale to create `scale.png`..." << std::endl;
  alma.readFromFile("alma.png");
  alma.scale(2);
  alma.writeToFile("scale2x.png");
  

  alma.readFromFile("alma.png");
  alma.scale(0.5);
  alma.writeToFile("scale-5x.png");  
  
  alma.readFromFile("alma.png");
  alma.scale(600,500);
  alma.writeToFile("scaleXX.png");
  alma.illinify();
  alma.writeToFile("illiniAlma.png");
  

  return 0;
}
