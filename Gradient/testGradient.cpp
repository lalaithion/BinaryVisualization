#include "gradient.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char const *argv[])
{
	// create gradient object between red and green
	// note - a incorrect gradient file may cause tests
	// to fail. Most syntax errors lead to undefined behavior
	Gradient r2g ("red2green.gradient");
	float array [256*3];

	// put texture into array
	r2g.getTexture(array);

	// make sure no value is less than 0 or greater than 1
	for(int i = 0; i < 256*3; i++)
	{
		assert(array[i] >= 0);
		assert(array[i] <= 1);
	}

	// test some array values 
	// (approximate equality due to rounding and floats)
	assert(array[0] - 1 < 0.01);
	assert(array[1] < 0.01);
	assert(array[2] < 0.01);

	assert(array[381] - 1 < 0.01);
	assert(array[382] - 1 < 0.01);
	assert(array[383] < 0.01);

	assert(array[765] < 0.01);
	assert(array[766] - 1 < 0.01);
	assert(array[767] < 0.01);

	return 0;
}