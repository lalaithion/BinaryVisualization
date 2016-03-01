#ifndef GRADIENT_H
#define GRADIENT_H

#include <string>
#include <vector>

#include "interpolate.h"

class gradient
{
	std::vector<point> color_curve;
	std::string name;
	std::string blendingmode;
public:
	gradient(std::string filename, std::string mode = "hsv");
	rgb getcolor(double position);
	std::string getname();
	int toArray(float array[256*3]);
};

#endif