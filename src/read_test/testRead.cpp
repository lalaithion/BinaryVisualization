#include "readfile.h"
#include <assert.h>

int main()
{
	fileReader ascii ("ascii.txt");
    unsigned int * image;
    ascii.getImage(image);

	for(int i = 127; i < 256; i++) {
		for(int j = 127; j < 256; j++) {
			assert(image[i+(j*256)] == 0);
		}
	}

	fileReader jpeg ("test.jpeg");
	jpeg.getImage(image);

	for(int i = 0; i < 256; i++) {
		for(int j = 0; j < 256; j++) {
			assert(image[i+(j*256)] >= 0);
		}
	}
}
