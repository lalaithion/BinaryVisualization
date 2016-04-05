#ifndef READFILE_H
#define READFILE_H

#include <iostream>
#include <fstream>
#include <stdlib.h>

#define DX 256 //  X dimension
#define DY 256 //  Y dimension

using namespace std;

class fileReader {
    unsigned char image[DX * DY * 3];
    char* myfile;
public:
    int readFile();
    unsigned char* getImage();
    fileReader(char *myFileName);
private:
};



#endif // READFILE_H
