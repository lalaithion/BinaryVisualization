#ifndef BV_READ_FILE_H

#define BV_READ_FILE_H

int filePairs(std::string filename, int (*data)[256]);
/*  This function takes a filename and a data array, and increments the value of data[i][j]
each time the pair of bytes i and j appear in sequence in the data */

int normalizePairs(int (*data)[256], float (*normalized)[256]);
/*  This function finds the maximum value in the array and divides every other value in the 
array by it, and places these values in the normalized array */

#endif