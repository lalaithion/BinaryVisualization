#include <string.h>
#include <fstream>

#include "readFile.h"

int filePairs(std::string filename, int (*data)[256])
{
    std::fstream file;
    int length;

    file.open(filename);                // open input file
    file.seekg(0, std::ios::end);       // go to the end
    length = file.tellg();              // report location (this is the length)
    file.seekg(0, std::ios::beg);       // go back to the beginning
    char * buffer = new char[length];   // allocate memory for a buffer of appropriate dimension
    file.read(buffer, length);          // read the whole file into the buffer 
    file.close();                       // close file handle

    for(int i = 0; i < (length-1); i++) // go through buffer
    {
        data[buffer[i]][buffer[i+1]]++; // increment the value for each pair of characters
    }

    return 0;                           // everything worked, return 0.
}

int normalizePairs(int (*data)[256], float (*normalized)[256])
{
    int max = 0;
    for(int i = 0; i < 256; i++)
    {
        for(int j = 0; j <256; j++)
        {
            if(data[i][j] > max)
            {
                max = data[i][j];
            }
        }
    }
    for(int i = 0; i < 256; i++)
    {
        for(int j = 0; j <256; j++)
        {
            normalized[i][j] = ((double)data[i][j])/max;
        }
    }
    return 0;
}