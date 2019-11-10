#include "StickerSheet.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "Image.h"
#include <iostream>
#include <string>

using namespace cs225;
using namespace std;
//initializes the StickerSheet
StickerSheet::StickerSheet(const Image& picture, unsigned max){
	Sheet = new Image *[max];
	this->max_ = max;
	this->yCoords = new int[max];
	this->xCoords = new int[max];
	base_ = new Image(picture);
	for(unsigned i = 0; i < max_; i++){
		xCoords[i] = 0;
		yCoords[i] = 0;
		Sheet[i] = NULL;
	}
	
}
// destructor
StickerSheet::~StickerSheet(){ 
	//what am I deleting here? the entire base & Sheet?
	this->clear_();
}
// copy constructor
StickerSheet::StickerSheet(const StickerSheet& other){
	this->copy_(other);
}
// overloading the assignment operator
const StickerSheet& StickerSheet::operator=(const StickerSheet& other){
	if(this != &other){
		this->clear_();
		this->copy_(other);
	}
	return *this;
}
// Modifies the maximum number of stickers
void StickerSheet::changeMaxStickers(unsigned max){
    if(max == this->max_) return;
	if(max < this->max_){
		for(unsigned i = max; i < max_; i++){
			//losing stickers above max-1
			delete Sheet[i];
			Sheet[i] = NULL;
		}
	}
	else{
		//since max>max_ need to create new bigger arrays
		Image** newSheet = new Image *[max];
		int *newxCoords = new int[max];
		int *newyCoords = new int[max];
		//initialize the new array to default values
		for(unsigned j = 0; j < max; j++){
			newSheet[j] = NULL;
			newxCoords[j] = 0;
			newyCoords[j] = 0;
		}
		//copy values from the old/smaller array
		for(unsigned k = 0; k < max; k++){
			
		}
	} 
}

int StickerSheet::addSticker(Image & sticker, unsigned x, unsigned y){
	if(getCt() < max_){
	    for(unsigned i = 0; i < max_; ++i){
	        if(Sheet[i] == NULL){
	            xCoords[i] = x;
	            yCoords[i] = y;
	            Sheet[i] = new Image(sticker);
	            increaseCt();
	            return i;
	        }
	    }
	}
	return -1;
    /*Image& temp = &this;
	while(temp != NULL){
		temp + sizeof(Image);
	}
	*temp = new Image(sticker, x,y);*/
	//how do I iterate through these pointers, and when I get there how do I place
	//this sticker there with a x and y initialized to it. Only Stickers have x & y
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y){
    if(index >= max_ || index < 1) return false; // invalid layer index
    else{
        xCoords[index] = x;
        yCoords[index] = y;
        return true;
    }
}

void StickerSheet::removeSticker(unsigned index){
	//delete
}

Image* StickerSheet::getSticker(unsigned index) const{
	//how to check is the index is invalid
	return base_;
}

Image StickerSheet::render() const{
	return *base_;
}

void StickerSheet::increaseCt(){
	this->stickerCt_ = stickerCt_ + 1;
}
void StickerSheet::decreaseCt(){
	this->stickerCt_ = stickerCt_ - 1;
}
// returns pointer to base image
Image* StickerSheet::getBase(){
	return this->base_;
}
// helper method clear_
void StickerSheet::clear_(){
	for(unsigned i = 0; i < max_; ++i){
	    if(Sheet[i] != NULL){
            delete Sheet[i];
            Sheet[i] = NULL;
	    }
	}
	delete[] Sheet;
	delete[] xCoords;
	delete[] yCoords;
	Sheet = NULL;
	xCoords = NULL;
	yCoords = NULL;
}
// helper method copy_
void StickerSheet::copy_(const StickerSheet & other){
    this->stickerCt_ = other.stickerCt_;
	this->max_ = other.max_;
	this->base_ = new Image(*other.base_);
	this->xCoords = new int[max_];
	this->yCoords = new int[max_];
	// Sheet = new Image *[max_];
	for(unsigned i = 0; i < max_; i++){
		if(other.Sheet[i] != NULL){
			this->Sheet[i] = new Image(*(other.Sheet[i]));
		} else {
			Sheet[i] = NULL;
		}
		this->xCoords[i] = other.xCoords[i];
		this->yCoords[i] = other.yCoords[i];
	}
}

unsigned StickerSheet::getCt() {
    return this->stickerCt_;
}