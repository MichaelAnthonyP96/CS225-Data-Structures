#ifndef _STICKERSHEET_H_
#define _STICKERSHEET_H_
#include "Image.h"
#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include <iostream>
#include <string>

class StickerSheet {
public:
  StickerSheet(const Image &picture, unsigned max);
  ~StickerSheet();
  StickerSheet(const StickerSheet &other);
  const StickerSheet &operator=(const StickerSheet &other);
  void changeMaxStickers(unsigned max);
  int addSticker(Image &sticker, unsigned x, unsigned y);
  bool translate(unsigned index, unsigned x, unsigned y);
  void removeSticker(unsigned index);
  Image *getSticker(unsigned index) const;
  Image render() const;
  Image *getBase();

private:
  Image **Sheet;
  Image *base_;
  int *xCoords;
  int *yCoords;
  unsigned max_;
  unsigned stickerCt_;
  // bool* contain;
  void copy_(const StickerSheet &other);
  void clear_();
  void clean(double threshold);
};

#endif