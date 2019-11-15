/**
 * @file Image.h
 * Contains your declaration of the interface for the Image class.
 */

#ifndef IMAGE_H_
#define IMAGE_H_
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <string>
using namespace cs225;

class Image : public cs225::PNG{
	public:
		Image();//default constructor
		~Image();//default destructor
		Image(const Image &other);//copy constructor
		Image const & operator= (Image const & other);//overload '=' operator
		Image(unsigned int width, unsigned int height);//two parameter constructor
		void lighten();
		void lighten(double amount);
		void darken();
		void darken(double amount);
		void saturate();
		void saturate(double amount);
		void desaturate();
		void desaturate(double amount);
		void grayscale();
		void rotateColor(double degrees);
		void illinify();
		void scale(double factor);
		void scale(unsigned w, unsigned h);
		unsigned int getWidth() const;
		unsigned int getHeight() const;
	private:
		// unsigned int width_;
		// unsigned int height_;
		// HSLAPixel *imageData_;
		// HSLAPixel defaultPixel_;
		void _copy(Image const & other);
};

#endif
 