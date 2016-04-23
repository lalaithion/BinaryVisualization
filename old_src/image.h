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
    Image();
    Image(char* filename);
    ~Image();
    int load(char* filename);
    unsigned int* getBuffer();
    void getLinearNormalizedBuffer(float* normalized, float scale = 1);
    void getPowNormalizedBuffer(float* normalized, float exponent = 0.5);
    void getLogNormalizedBuffer(float* normalized, float base = E_CONST);
private:
    unsigned int* imageBuffer;
    int getMax();
};


/*using namespace std;

class fileReader {
    unsigned int image[DX * DY];
    char* myfile;
    int readFile();
public:
    int getMax();
    unsigned int* getBuffer();
    fileReader(char *myFileName);
};
*/
#endif
