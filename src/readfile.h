#ifndef READFILE_H
#define READFILE_H

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <math.h>

#define DX 256 //  X dimension
#define DY 256 //  Y dimension
#define BLOCK_SIZE 32
#define IMAGE_SIZE 256
#define E_CONST 2.718281828459045235360287471352

int readfile(char* filename, unsigned int* image);

int getMax(unsigned int* image);

void linearNormalize(unsigned int* image, float* normalized, float scale = 1);
void powNormalize(unsigned int* image, float* normalized, float exponent = 0.5);
void logNormalize(unsigned int* image, float* normalized, float base = E_CONST);



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
#endif // READFILE_H
