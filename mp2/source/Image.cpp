#include "include/Image.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <math.h>

Image::Image() : PNG() { // default constructor
    this->imageData_ = NULL;
}

Image::~Image(){ // destructor
	//delete[] this->cs225::PNG::imageData_;
}

Image::Image(const Image &other) : PNG(other.getWidth(), other.getHeight()){ // copy constructor
    this->Image::_copy(other);
}
Image const & Image::operator= (Image const & other){
	if (this != &other) { Image::_copy(other); }
    return *this;
}

Image::Image(unsigned int width, unsigned int height) : PNG(width, height) {
}

void Image::_copy(Image const & other) {
	// Clear self
    delete[] imageData_;

    // resize the imageData array to the new size
    this->cs225::PNG::resize(other.getWidth(), other.getHeight());

    // Copy `other` to self
    imageData_ = new HSLAPixel[this->getWidth() * this->getHeight()];
    for (unsigned i = 0; i < this->getWidth() * this->getHeight(); ++i) {
      imageData_[i] = other.imageData_[i];
    }
}

/*
Lighten an Image by increasing the luminance of every pixel by 0.1.
This function ensures that the luminance remains in the range [0, 1].
*/
void Image::lighten(){
	for (unsigned x = 0; x < this->cs225::PNG::width(); x++) {
    	for (unsigned y = 0; y < this->cs225::PNG::height(); y++) {
      	    cs225::HSLAPixel & pixel = this->cs225::PNG::getPixel(x, y);

            pixel.l = pixel.l + 0.1;
            if(pixel.l > 1.0)
                pixel.l = 1.0;
            else if(pixel.l < 0.0)
                pixel.l = 0.0;
            }
	}
}
/*
Lighten an Image by increasing the luminance of every pixel by amount.
This function ensures that the luminance remains in the range [0, 1].
Parameters: amount (The desired increase in luminance.)
*/
void Image::lighten(double amount){
	for (unsigned x = 0; x < this->cs225::PNG::width(); x++) {
    	for (unsigned y = 0; y < this->cs225::PNG::height(); y++) {
      	cs225::HSLAPixel & pixel = this->cs225::PNG::getPixel(x, y);

	    pixel.l = pixel.l + amount;
		if(pixel.l > 1.0)
			pixel.l = 1.0;
		else if(pixel.l < 0.0)
			pixel.l = 0.0;
		}
	}
}
/*
Darken an Image by decreasing the luminance of every pixel by 0.1.
This function ensures that the luminance remains in the range [0, 1].
*/
void Image::darken(){
	for (unsigned x = 0; x < this->cs225::PNG::width(); x++) {
    	for (unsigned y = 0; y < this->cs225::PNG::height(); y++) {
      	cs225::HSLAPixel & pixel = this->cs225::PNG::getPixel(x, y);

	    pixel.l = pixel.l - 0.1;
		if(pixel.l > 1.0)
			pixel.l = 1.0;
		else if(pixel.l < 0.0)
			pixel.l = 0.0;
		}
	}
}
/*
Darkens an Image by decreasing the luminance of every pixel by amount.
This function ensures that the luminance remains in the range [0, 1].
Parameters: amount (The desired decrease in luminance)
*/
void Image::darken(double amount){
	for (unsigned x = 0; x < this->cs225::PNG::width(); x++) {
    	for (unsigned y = 0; y < this->cs225::PNG::height(); y++) {
      	cs225::HSLAPixel & pixel = this->cs225::PNG::getPixel(x, y);

	    pixel.l -= amount;
		if(pixel.l > 1.0)
			pixel.l = 1.0;
		else if(pixel.l < 0.0)
			pixel.l = 0.0;
		}
	}
}
/*
Saturates an Image by increasing the saturation of every pixel by 0.1.
This function ensures that the saturation remains in the range [0, 1].
*/
void Image::saturate(){
	for (unsigned x = 0; x < this->cs225::PNG::width(); x++) {
    	for (unsigned y = 0; y < this->cs225::PNG::height(); y++) {
      	cs225::HSLAPixel & pixel = this->cs225::PNG::getPixel(x, y);

	    pixel.s += 0.1;
		if(pixel.s > 1.0)
			pixel.s = 1.0;
		else if(pixel.s < 0.0)
			pixel.s = 0.0;
		}
	}
}
/*
Saturates an Image by increasing the saturation of every pixel by amount.
This function ensures that the saturation remains in the range [0, 1].
Parameters: amount (The desired increase in saturation.)
*/
void Image::saturate(double amount){
	for (unsigned x = 0; x < this->cs225::PNG::width(); x++) {
    	for (unsigned y = 0; y < this->cs225::PNG::height(); y++) {
      	cs225::HSLAPixel & pixel = this->cs225::PNG::getPixel(x, y);

	    pixel.s += amount;
		if(pixel.s > 1.0)
			pixel.s = 1.0;
		else if(pixel.s < 0.0)
			pixel.s = 0.0;
		}
	}
}
/*
Desaturates an Image by decreasing the saturation of every pixel by 0.1.
This function ensures that the saturation remains in the range [0, 1].
*/
void Image::desaturate(){
	for (unsigned x = 0; x < this->cs225::PNG::width(); x++) {
    	for (unsigned y = 0; y < this->cs225::PNG::height(); y++) {
      	cs225::HSLAPixel & pixel = this->cs225::PNG::getPixel(x, y);

	    pixel.s -= 0.1;
		if(pixel.s > 1.0)
			pixel.s = 1.0;
		else if(pixel.s < 0.0)
			pixel.s = 0.0;
		}
	}
}
/*
Desaturate an Image by decreasing the saturation of every pixel by amount.
This function ensures that the saturation remains in the range [0, 1].
Parameters :amount	(The desired decrease in saturation.)
 */
void Image::desaturate(double amount){
	for (unsigned x = 0; x < this->cs225::PNG::width(); x++) {
    	for (unsigned y = 0; y < this->cs225::PNG::height(); y++) {
      	cs225::HSLAPixel & pixel = this->cs225::PNG::getPixel(x, y);

	    pixel.s -= amount;
		if(pixel.s > 1.0)
			pixel.s = 1.0;
		else if(pixel.s < 0.0)
			pixel.s = 0.0;
		}
	}	
}
//Turns the image grayscale. 
void Image::grayscale(){
	for (unsigned x = 0; x < this->cs225::PNG::width(); x++) {
    	for (unsigned y = 0; y < this->cs225::PNG::height(); y++) {
      	cs225::HSLAPixel & pixel = this->cs225::PNG::getPixel(x, y);
	    pixel.s = 0;
    }
  }
}
/*
Rotates the color wheel by degrees.
This function ensures that the hue remains in the range [0, 360].
Parameters
    degrees	The desired amount of rotation. 
*/
void Image::rotateColor(double degrees){
	for (unsigned x = 0; x < this->cs225::PNG::width(); x++) {
    	for (unsigned y = 0; y < this->cs225::PNG::height(); y++) {
      	cs225::HSLAPixel & pixel = this->cs225::PNG::getPixel(x, y);

	    // `pixel` is a pointer to the memory stored inside of the PNG `image`,
	    // which means you're changing the image directly.  No need to `set`
	    // the pixel since you're directly changing the memory of the image.
	    pixel.h = pixel.h + degrees;
		if(pixel.h > 360.0){
			pixel.h = fmod((pixel.h), 360.0);
		}
		else if(pixel.h < 0.0){
			pixel.h = pixel.h + 360;
		}
	}
}
}
// Illinify the image
void Image::illinify(){
for(unsigned int x = 0; x < cs225::PNG::width(); x++){
  for(unsigned int y = 0; y < cs225::PNG::height(); y++){
    // Get a reference to the pixel at (x,y):
    cs225::HSLAPixel & pixel = this->cs225::PNG::getPixel(x,y);
    // Check to see if the hue is closer to blue or orange
    if((pixel.h <= 293.5) && (pixel.h >= 113.5)){
    // set the pixel to blue
      pixel.h = 216;
    }
    else {
      //set the pixel to orange
      pixel.h = 11;
    }
  }
}
}
/*
Scale the Image by a given factor.
For example:
    A factor of 1.0 does not change the image.
    A factor of 0.5 results in an image with half the width and half the height.
    A factor of 2 results in an image with twice the width and twice the height.
This function both resizes the Image and scales the contents.
Parameters :factor (Scale factor.)
*/
void Image::scale(double factor){
	if(factor <= 0){
		std::cout << factor << std::endl;
		std::cout << "Cannot scale an image by a factor of 0 or less. " <<  std::endl;
	}
	else{
		int oldWidth = this->cs225::PNG::width();// 360
		int oldHeight = this->cs225::PNG::height();// 100
		int newWidth = int(oldWidth * factor); //720
		int newHeight = int(oldHeight * factor);
		
		// rescale the image before or after the depending on if shrinking or expanding
		if(factor > 1.0 ){ 
			this->cs225::PNG::resize(newWidth,newHeight);
		
			for(int x = newWidth-1; (x > (-1)); x--){
		  		for(int y = newHeight-1; (y > (-1)); y--){
			    // Get a pointer to the pixel at (x,y):
			    cs225::HSLAPixel *pixelo = &this->cs225::PNG::getPixel(int(x/factor),int(y/factor));
			    HSLAPixel *pixeln = &this->cs225::PNG::getPixel(x,y); 

			    pixeln->l = pixelo->l;
			    pixeln->h = pixelo->h;
			    pixeln->s = pixelo->s;
			    pixeln->a = pixelo->a;
			  	}
			}
		}
		else{
			for(int x = 0; x < oldWidth; x++){
		  		for(int y = 0; y < oldHeight; y++){
			    // Get a pointer to the pixel at (x,y):
			    cs225::HSLAPixel *pixelo = &this->cs225::PNG::getPixel(x,y);
			    HSLAPixel *pixeln = &this->cs225::PNG::getPixel(int(x*factor),int(y*factor)); 

			    pixeln->l = pixelo->l;
			    pixeln->h = pixelo->h;
			    pixeln->s = pixelo->s;
			    pixeln->a = pixelo->a;
			  	}
			}
			this->cs225::PNG::resize(newWidth,newHeight);	
		}
	}
}

/*
Scales the image to fit within the size (w x h).
This function preserves the aspect ratio of the image, so the result will always be an image of width w or of height h (not necessarily both).
This function both resizes the Image and scales the contents.
Parameters
    w	Desired width of the scaled Image
    h	Desired height of the scaled Image
*/
void Image::scale(unsigned w, unsigned h){
	int oldWidth = this->cs225::PNG::width();
	int oldHeight = this->cs225::PNG::height();
	double aspectRatio = double(oldWidth/oldHeight);
	if((w/aspectRatio ) < h){
		Image::scale(double(h)/double(oldHeight));
	}
	else{
		Image::scale(double(w)/double(oldWidth));
	}

}
// \brief returns Image width
unsigned int Image::getWidth() const {
	return this->cs225::PNG::width();
}
// \brief returns Image height
unsigned int Image::getHeight() const {
	return this->cs225::PNG::height();
}