#include <string>
#include <fstream>
#include <algorithm>
#include <stdlib.h>
#include <vector>
#include <cstdlib>

#include "interpolate.h"
#include "gradient.h"

// http://stackoverflow.com/questions/5891610/how-to-remove-characters-from-a-string
void removeCharsFromString( std::string &str, std::string charsToRemove )
{
    const char *  charls = charsToRemove.c_str();
    for ( unsigned int i = 0; i < strlen(charls); ++i )
    {
       str.erase( remove(str.begin(), str.end(), charls[i]), str.end() );
    }
}

bool pointSort (point i,point j) 
{
	return (i.position<j.position);
}


gradient::gradient(std::string filename, std::string mode)
{
	blendingmode = mode;

	std::fstream file (filename, std::fstream::in);
	std::string line;


	while(std::getline(file,line).good())
	{
		if (line[0] == '/')
		{
			;
		}
		else if (line[0] == '\0')
		{

		}
		else if (line[0] == '"')
		{
			int endquote = line.find("\"",1);
			name = line.substr(1,endquote);
		}
		else
		{
			removeCharsFromString(line," \t#");
			int separator = line.find('>');
			std::string p = line.substr(0,separator);
			std::string c =line.substr(separator+1,6);
			float red = strtol(c.substr(0,2).c_str(),NULL,16)/255.0;
			float green = strtol(c.substr(2,2).c_str(),NULL,16)/255.0;
			float blue = strtol(c.substr(4,2).c_str(),NULL,16)/255.0;
			rgb color = {red,green,blue};
			point current = {std::stod(p),color};
			color_curve.push_back(current);
		}
	}
	std::sort(color_curve.begin(),color_curve.end(),pointSort);
}

rgb gradient::getcolor(double position)
{
	if(position >= 1)
	{
		return color_curve.back().color;
	}
	if(position <= 0)
	{
		return color_curve.front().color;
	}
	int loc;
	for(int i = 0; i < color_curve.size(); i++)
	{
		if(color_curve[i].position == position)
		{
			return color_curve[i].color;
		}
		if(color_curve[i].position < position)
		{
			loc = i;
		}
	}
	return interpolate(position,color_curve[loc],color_curve[loc+1], blendingmode);
}

std::string gradient::getname()
{
	return name;
}
