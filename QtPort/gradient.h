#ifndef GRADIENT_H
#define GRADIENT_H

#include <string>
#include <vector>

#include "interpolate.h"

class Gradient
{
private:
	//private variables
	std::vector<point> colorCurve;
	std::string name;
	bool polar;
	//private helper functions
	bool parseSettings(std::string);
	std::string parseName(std::string);
	point parseData(std::string);
	double parseLoc(std::string);
	rgb parseColor(std::string);
	rgb parseHex(std::string);
	rgb parseTup(std::string);
	static bool pointSort (point,point); 

public:
	//constructor
	Gradient(std::string);
	//accessor functions
    void getTexture(float*);
	std::string getName();
};


#endif
