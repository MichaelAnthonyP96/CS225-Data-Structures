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
   /**
    * Image default constructor.
    */
    Image(); // default constructor
   /**
    * Image destructor
    */
    ~Image(); // default destructor
   /**
    * Image copy constructor
    * @param other Image obj to copy.
    */
    Image(const Image &other); // copy constructor
   /**
    * Overloaded image assignment operator
    * @param other Right hand side image obj with regard to the binary operator.
    * @return A const Image reference L-value
    */
    Image const & operator= (Image const & other); // overload '=' operator
   /**
    * Image two parameter constructor.
    * @param width Image dimension in the horizontal direction.
    * @param height Image dimension in the vertical direction.
    */
    Image(unsigned int width, unsigned int height); // two parameter constructor
   /**
    * Lighten every pixel in the image by 0.1
    */
    void lighten();
   /**
    * Lightens every pixel in image by a specified amount
    * @param amount Amount to lighten the image by, valid values range from 0 - 1.
    */
    void lighten(double amount);
   /**
    * Darken every pixel in the image by 0.1
    */
    void darken();
   /**
    * Darken every pixel in the image by a specified amount.
    * @param amount Amount to darken the image by, valid values range from 0 - 1.
    */
    void darken(double amount);
   /**
    * Saturate every pixel in the image by 0.1
    */
    void saturate();
   /**
    * Saturate every pixel in the image by a specified amount.
    * @param amount Amount to saturate the image by, valid values range from 0 - 1.
    */
    void saturate(double amount);
   /**
    * Desaturate every pixel in the image by 0.1
    */
    void desaturate();
   /**
    * Desaturate every pixel in the image by a specified amount.
    * @param amount Amount to darken the image by, valid values range from 0 - 1.
    */
    void desaturate(double amount);
   /**
    * Convert the image to greyscale.
    */
    void grayscale();
   /**
    * Rotate the image by a specified degree. TODO: verify that the rotation is clockwise
    * @param degrees Angle to rotate the image by clockwise, valid values range from 0 - 1.
    */
    void rotateColor(double degrees);
   /**
    * Convert the image to orange and blue.
    */
    void illinify();
   /**
    * Scale the Image by a given factor.
    * For example:
    *    A factor of 1.0 does not change the image.
    *    A factor of 0.5 results in an image with half the width and half the height.
    *    A factor of 2 results in an image with twice the width and twice the height.
    * This function both resizes the Image and scales the contents.
    * @param factor Scale factor.
    */
    void scale(double factor);
   /**
    * Scale the Image to a desired width and height.
    * @param w The size to scale the horizontal dimension to.
    * @param h The size to scale the vertical dimension to.
    */
    void scale(unsigned w, unsigned h);
   /**
    * Get the width of the image.
    * @return unsigned int the size of the image in the horizontal dimension.
    */
    unsigned int getWidth() const;
   /**
    * Get the height of the image.
    * @return unsigned int the size to the image in the vertical dimension.
    */
    unsigned int getHeight() const;
private:
    void _copy(Image const & other);
};

#endif
 