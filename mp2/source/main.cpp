#include "include/Image.h"
#include "include/StickerSheet.h"

int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //

  Image alma;
  alma.readFromFile("tests/SourceImages/alma.png");
  StickerSheet sheet(alma, 5);

  Image gorilla;
  gorilla.readFromFile("tests/SourceImages/GorillaSelfie.png");
  gorilla.clean(0.1);
  sheet.addSticker(gorilla, 540, 345);

  Image dragon;
  dragon.readFromFile("tests/SourceImages/dragon.png");
  dragon.clean(0.01);
  dragon.scale(0.35);
  sheet.addSticker(dragon, 645, 20);

  Image cyborg;
  cyborg.readFromFile("tests/SourceImages/cyborg.png");
  cyborg.clean(0.05);
  sheet.addSticker(cyborg, 5, 85);

  Image result = sheet.render();
  result.writeToFile("testResults/myImage.png");
  return 0;
}
