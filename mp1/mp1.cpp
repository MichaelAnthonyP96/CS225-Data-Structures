#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <math.h>
#include <string>

using namespace cs225;


void rotate(std::string inputFile, std::string outputFile) {
    // Part 2
	//initializes the 'in' PNG as an empty PNG instance
	cs225::PNG in;
	//reads the pixel information from the name of the inputFile
	in.readFromFile(inputFile);
	//initializes the 'out' PNG as the same size as the 'in' PNG
	cs225::PNG out(in.width(),in.height());
	//rotates the image going pixel by pixel
	for(unsigned i=0; (i <= (in.width()-1)); i++){
		for(unsigned j=0; (j <= (in.height()-1)); j++){
			//gets a pointer to the pixel in the 'in' PNG
			HSLAPixel * pixelIn = in.getPixel(i, j);
			//gets a pointer to the pixel in the 'out' PNG where the 'in' pixel will go
			HSLAPixel * pixelOut = out.getPixel((in.width()-1)-i,(in.height()-1)-j);
			//dereferences the pointer value of the 'out' PNG and sets it equal to the
			//dereferenced pointer of the 'in' PNG
			*pixelOut = *pixelIn;
		}
	}
	//writes the out PNG information to the outputFile
	out.writeToFile(outputFile);
}

PNG myArt(unsigned int width, unsigned int height) {
	PNG png(width, height);
	// Part 3
  	double hueIncrement = 360/(double(width)-1.0);
  	double saturationIncrement = 0.5/(double(width)-1.0);
  	double luminanceIncrement = 1.0/((double(height)/2.0)-1.0);
  	//double alphaIncrement = 0.7/((double(height)-1.0) + (double(width)-1.0));
	for(unsigned int i = 0; i < (width); i++){
  		for(unsigned int j = 0; j < (height); j++){
  			HSLAPixel * pixelPtr = png.getPixel(i,j);
  			//implements a horizontal spectrum of all hues
  			pixelPtr->h = ceil(hueIncrement * double(i));
  			//saturation spectrum vertically
  			pixelPtr->s = 0.5 + saturationIncrement * double(i); 
  			pixelPtr->l = 1.0 - (luminanceIncrement * sqrt(pow(double(400.0-i),2) 
  				+ pow(double(400.0-j),2)));
  			pixelPtr->a = 1.0;// - (alphaIncrement * double(i + j));
  		}
  	}

  return png;
}
