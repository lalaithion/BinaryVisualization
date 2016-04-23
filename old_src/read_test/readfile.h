#ifndef READFILE_H
#define READFILE_H

#include <iostream>
#include <fstream>
#include <stdlib.h>

#define DX 256 //  X dimension
#define DY 256 //  Y dimension
#define BLOCK_SIZE 32

using namespace std;

class fileReader {
    unsigned int image[DX * DY];
    char* myfile;
    int readFile();
public:
    int getImage(unsigned int *returnloc);
    fileReader(char *myFileName);
};

#endif // READFILE_H
