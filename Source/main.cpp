#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "readFile.h"

int main(int argc, char* argv[])
{
	std::string filename = "testFile.txt";
	if(argc != 1)
	{
		filename = argv[1];
	}

	int data[256][256] = {0};
	filePairs(filename, data);

	float norm[256][256] = {0.0};
	normalizePairs(data, norm);
	return 0;
}