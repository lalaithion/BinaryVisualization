#include "readFile.h"

int main(int argc, char* argv[])
{
	std::string filename = "testFile.txt";
	if(argc != 1)
	{
		filename = argv[1];
	}
}