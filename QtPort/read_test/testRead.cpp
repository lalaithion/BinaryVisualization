#include "readfile.h"
#include <assert.h>

int main()
{
	fileReader ascii ("ascii.txt");
	unsigned char * image = ascii.getImage();

	for(int i = 127; i < 256; i++) {
		for(int j = 127; j < 256; j++) {
			assert(image[i+(j*256)] == 0);
		}
	}

	fileReader jpeg ("test.jpeg");
	image = jpeg.getImage();

	for(int i = 0; i < 256; i++) {
		for(int j = 0; j < 256; j++) {
			assert(image[i+(j*256)] >= 0);
		}
	}
}