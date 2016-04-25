#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <math.h>

#define FILE_BUFFER_SIZE 1024
#define IMAGE_BUFFER_SIZE 256
#define E_CONST 2.718281828459045235360287471352

class Image {
public:
    /*
     *  Default constructor does nothing.
     */
    Image();
    /*
     *  If given a filename as a char* in the constructor, it will atomatically load that file.
     */
    Image(char* filename);
    ~Image();
    /*
     *  Loads the file whose name is passed in into a buffer of weights.
     */
    int load(char* filename);
    /*
     *  Returns a pointer to the buffer where the file is stored, if there is one.
     */
    unsigned int* getBuffer();
    /*
     *  Linearly normalizes the buffer and puts the result in an the array of floats that's passed in.
     *  The array must be 256x256 or the program will try to write out of bounds.
     *  The scale argument is simply a linear scale.
     */
    void getLinearNormalizedBuffer(float* normalized, float scale = 1);
    /*
     *  Exponentially normalizes the buffer and puts the result in an the array of floats that's passed in.
     *  The array must be 256x256 or the program will try to write out of bounds.
     *  The exponent argument determines the steepness of the exponential curve.
     */
    void getPowNormalizedBuffer(float* normalized, float exponent = 0.5);
    /*
     *  Logarithmically normalized the buffer and puts the result in an the array of floats that's passed in.
     *  The array must be 256x256 or the program will try to write out of bounds.
     *  The base arguement determines the steepness of the logarithmic curve.
     */
    void getLogNormalizedBuffer(float* normalized, float base = E_CONST);
private:
    /*
     *  Buffer used to store the data read from the file before normalization.
     */
    unsigned int* imageBuffer;
    /*
     *  Gets the maximum value in the buffer for use in the normalization functions.
     */
    int getMax();
};
#endif
