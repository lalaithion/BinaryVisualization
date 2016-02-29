#include <iostream>
#include <string>

#include "gradient.h"

int main(int argc, char *argv[])
{
	if(argc == 1)
	{
		return 0;
	}

	std::string filename = argv[1];
	gradient example (filename);
	rgb inter = {0,0,0};
	std::cout << example.getname() << std::endl;
	for(double i = 0.0; i <= 1.001; i += 0.01)
	{
		inter = example.getcolor(i);
		std::cout << i << "\t";
		std::cout << int(inter.r * 255) << ",";
		std::cout << int(inter.g * 255) << ",";
		std::cout << int(inter.b * 255) << std::endl;
	}
}