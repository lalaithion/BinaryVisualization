#include "interpolate.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	rgb alpha, beta;
	xyz temp;

	srand(time(NULL));

	for(int i=0; i<4; i++){
        alpha.r = (rand() % 256)/255.0;
        alpha.g = (rand() % 256)/255.0;
        alpha.b = (rand() % 256)/255.0;
        temp = rgb2xyz(alpha);
        beta = xyz2rgb(temp);
        printf("%s\n",printcolor(alpha));
        printf("%s\n",printcolor(temp));
        printf("%s\n",printcolor(beta));
        printf("------------------\n");
    }

	return 0;
}