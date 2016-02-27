#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <iostream>

int filePairs(std::string filename, int data[256][256]);
/*  This function takes a filename and a data array, and increments the value of data[i][j]
each time the pair of bytes i and j appear in sequence in the data */

int normalizePairs(int data[256][256], float normalized[256][256]);
/*  This function finds the maximum value in the array and divides every other value in the 
array by it, and places these values in the normalized array */