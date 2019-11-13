#include "Image.h"
#include "StickerSheet.h"

int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //

    Image alma; alma.readFromFile("tests/alma.png");
    Image i;    i.readFromFile("tests/i.png");

    StickerSheet sheet(alma, 5);
    sheet.addSticker(i, 20, 200);

    Image expected;
    expected.readFromFile("tests/expected.png");

    //REQUIRE( sheet.render() == expected );

  return 0;
}
