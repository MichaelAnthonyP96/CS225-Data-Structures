#include "include/StickerSheet.h"
#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "include/Image.h"
#include <iostream>
#include <string>

using namespace cs225;
using namespace std;
// initializes the StickerSheet
StickerSheet::StickerSheet(const Image &picture, unsigned max) {
  Sheet = new Image *[max];
  this->stickerCt_ = 0;
  this->max_ = max;
  this->yCoords = new int[max];
  this->xCoords = new int[max];
  base_ = new Image(picture);
  for (unsigned i = 0; i < max_; i++) {
    xCoords[i] = 0;
    yCoords[i] = 0;
    Sheet[i] = NULL;
  }
}
// destructor
StickerSheet::~StickerSheet() { this->clear_(); }
// copy constructor
StickerSheet::StickerSheet(const StickerSheet &other) { this->copy_(other); }
// overloading the assignment operator
const StickerSheet &StickerSheet::operator=(const StickerSheet &other) {
  if (this != &other) {
    this->clear_();
    this->copy_(other);
  }
  return *this;
}
// Modifies the maximum number of stickers
void StickerSheet::changeMaxStickers(unsigned max) {
  if (max == this->max_)
    return;
  if (max <= this->max_) {
    for (unsigned i = max; i < max_; ++i) {
      removeSticker(i);
    }
    this->max_ = max;
  } else {
    // since max > max_ need to create new bigger array
    Image **newSheet = new Image *[max];
    int *newxCoords = new int[max];
    int *newyCoords = new int[max];
    // Copy over the old stickers to the new larger array
    for (unsigned j = 0; j < this->stickerCt_; ++j) {
      if (Sheet[j] != NULL) {
        newSheet[j] = new Image(*Sheet[j]);
        newxCoords[j] = xCoords[j];
        newyCoords[j] = yCoords[j];
      }
    }
    // set remaining pointers to NULL
    for (unsigned k = this->stickerCt_; k < max; ++k) {
      newSheet[k] = NULL;
    }
    // Delete the old sticker array
    delete[] Sheet;
    // Assign the new larger array to the current StickerSheet obj
    this->Sheet = newSheet;
    this->xCoords = newxCoords;
    this->yCoords = newyCoords;
    this->max_ = max;
  }
}

int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y) {
  if (this->stickerCt_ < max_) {
    for (unsigned i = 0; i < max_; ++i) {
      if (Sheet[i] == NULL) {
        xCoords[i] = x;
        yCoords[i] = y;
        Sheet[i] = new Image(sticker);
        this->stickerCt_++;
        return i;
      }
    }
  }
  return -1;
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
  if (index >= max_ || index < 0 || Sheet[index] == NULL)
    return false; // invalid layer index
  else {
    xCoords[index] = x;
    yCoords[index] = y;
    return true;
  }
}

void StickerSheet::removeSticker(unsigned index) {
  if (index >= max_ || Sheet[index] == NULL)
    return;
  else {
    delete Sheet[index];
    Sheet[index] = NULL;
    xCoords[index] = 0;
    yCoords[index] = 0;
    this->stickerCt_--;
  }
}

Image *StickerSheet::getSticker(unsigned index) const {
  if (index >= max_ || index < 0)
    return NULL;
  else
    return Sheet[index];
}

Image StickerSheet::render() const {
  Image *canvas = new Image(*(this->base_));
  unsigned xMax = canvas->width();
  unsigned yMax = canvas->height();
  for (unsigned i = 0; i < max_; ++i) {
    if (Sheet[i] != NULL) {
      unsigned x = xCoords[i] + Sheet[i]->width();
      unsigned y = yCoords[i] + Sheet[i]->height();
      xMax = x > xMax ? x : xMax;
      yMax = y > yMax ? y : yMax;
    }
  }
  canvas->resize(xMax, yMax);
  for (unsigned i = 0; i < max_; ++i) {
    if (Sheet[i] != NULL) {
      for (unsigned xPos = xCoords[i]; xPos < xCoords[i] + Sheet[i]->width();
           ++xPos) {
        for (unsigned yPos = yCoords[i]; yPos < yCoords[i] + Sheet[i]->height();
             ++yPos) {
          HSLAPixel &canvasPixel = canvas->getPixel(xPos, yPos);
          HSLAPixel &stickerPixel =
              Sheet[i]->getPixel(xPos - xCoords[i], yPos - yCoords[i]);
          if (stickerPixel.a > 0.) {
            std::cout << stickerPixel.a << std::endl;
            //                        canvasPixel.h = stickerPixel.h;
            //                        canvasPixel.s = stickerPixel.s;
            //                        canvasPixel.l = stickerPixel.l;
            //                        canvasPixel.a = stickerPixel.a;
            canvasPixel = stickerPixel;
          }
        }
      }
    }
  }
  return *canvas;
}

// returns pointer to base image
Image *StickerSheet::getBase() { return this->base_; }
// helper method clear_
void StickerSheet::clear_() {
  // remove base image
  delete base_;
  base_ = NULL;
  // remove all stickers
  //	for(unsigned i = 0; i < max_; ++i){
  //	    if(Sheet[i] != NULL){
  //            delete Sheet[i];
  //            Sheet[i] = NULL;
  //	    }
  //	}
  delete[] Sheet;
  delete[] xCoords;
  delete[] yCoords;
  Sheet = NULL;
  xCoords = NULL;
  yCoords = NULL;
}
// helper method copy_
void StickerSheet::copy_(const StickerSheet &other) {
  this->stickerCt_ = other.stickerCt_;
  this->max_ = other.max_;
  this->base_ = new Image(*other.base_);
  this->xCoords = new int[max_];
  this->yCoords = new int[max_];
  this->Sheet = new Image *[max_];
  // Sheet = new Image *[max_];
  for (unsigned i = 0; i < max_; i++) {
    if (other.Sheet[i] != NULL) {
      this->Sheet[i] = new Image(*(other.Sheet[i]));
    } else {
      Sheet[i] = NULL;
    }
    this->xCoords[i] = other.xCoords[i];
    this->yCoords[i] = other.yCoords[i];
  }
}
