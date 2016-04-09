#include <stdio.h>
#include <iostream>
#include <ctype.h>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iomanip>

#include "gradient.h"

Gradient::Gradient(std::string gradient)
{
    std::stringstream stream;
    stream << gradient;
	std::string line;
	std::string stripped;
	polar = true;
    while(getline(stream,line))
    {
        //stripped = line;
        std::cout << "This is a test!" << '\n';
        //stripped.erase(std::remove_if(stripped.begin(), stripped.end(), isspace), stripped.end());
        std::cout << "Izaak needs to hire higher quality strippers\n";
        if(line[0] == '"')
		{
            std::cout << "ParseName!\n";
			name = parseName(line);
		}
        else if(line[0] == 'u')
		{
            std::cout << "Polar something!\n";
			polar = parseSettings(line);
		}
        else if(line[0] == '/')
		{

		}
        else if(line.size() < 3)
		{
			
		}
		else
		{
            std::cout << "Well, there's always the color curve\n";
			colorCurve.push_back(parseData(line));
		}
        std::cout <<"Line ended!\n";
    }
    std::sort(colorCurve.begin(),colorCurve.end(),pointSort);\
}

bool Gradient::pointSort (point i,point j) 
{
	return (i.position<j.position);
}

void Gradient::getTexture(float * array)
{
	rgb current;
	int index = 0;
	for(int i = 0; i < 256; i++)
    {
    	double position = i/256.0;
    	if (position > colorCurve[index+1].position)
    	{
    		index++;
    	}
        current = interpolate(position,colorCurve[index],colorCurve[index+1],"hsv");
        array[3*i] = current.r;
        array[3*i + 1] = current.g;
        array[3*i + 2] = current.b;
        //printf("%d, %f: %d, %d, %d\n",index,position,(int)(current.r*255.0),(int)(current.g*255.0),(int)(current.b*255.0));
    }
}

std::string Gradient::getName()
{
	return name;
}


std::string Gradient::parseName(std::string line)
{
	std::string comment = "//";
	int comPos = line.find(comment);
	line = line.substr(1,comPos);
	int endquote = line.find("\"");
	line = line.substr(0,endquote);
	return line;
}

bool Gradient::parseSettings(std::string line)
{
	line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
	std::string comment = "//";
	int comPos = line.find(comment);
	line = line.substr(1,comPos);
	int use = line.find("use");
	line = line.substr(use+3);
	if(line.compare("hsv") == 0)
	{
		return true;
	}
	else if (line.compare("rgb") == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

point Gradient::parseData(std::string line)
{
	std::string delimiter = "->";
	std::string comment = "//";
	int delPos = line.find(delimiter);
	std::string locStr = line.substr(0,delPos);
	double location = parseLoc(locStr);
	int comPos = line.find(comment);
	std::string colStr;
	if(comPos == std::string::npos)
	{
		colStr = line.substr(delPos+2);
	}
	else
	{
		colStr = line.substr(delPos+2,comPos);
	}
	rgb color = parseColor(colStr);
	point result;
	result.color = color;
	result.position = location;
	return result;
}

double Gradient::parseLoc(std::string line)
{
	line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
    return atof(line.c_str());
}

rgb Gradient::parseColor(std::string line)
{
	line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
	if (line[0] == '#')
	{
		return parseHex(line);
	}
	else if (line[0] == '(')
	{
		return parseTup(line);
	}
	else
	{
		rgb result;
		result.r = 0;
		result.g = 0;
		result.b = 0;
		return result;
	}
}

rgb Gradient::parseHex(std::string line)
{
	std::string redStr = line.substr(1,2);
	std::string greenStr = line.substr(3,2);
	std::string blueStr = line.substr(5,2);
    int redNum, greenNum, blueNum;
    std::istringstream colorStream(redStr + " " + blueStr + " " + greenStr);
    colorStream >> std::setbase(16) >> redNum >> greenNum >> blueNum;
	rgb result;
    result.r = redNum / 255.0;
    result.g = greenNum / 255.0;
    result.b = blueNum / 255.0;
	return result;
}

rgb Gradient::parseTup(std::string line)
{
	line.erase(std::remove(line.begin(), line.end(), '('), line.end());
	line.erase(std::remove(line.begin(), line.end(), ')'), line.end());
	std::string separator = ",";
	int firstComma = line.find(separator);
	int secondComma = line.find(separator, firstComma + 1);
	std::string redStr = line.substr(0,firstComma);
	std::string greenStr = line.substr(firstComma+1,secondComma-firstComma);
	std::string blueStr = line.substr(secondComma+1);
    float redNum = atoi(redStr.c_str())/255.0;
    float greenNum = atoi(greenStr.c_str())/255.0;
    float blueNum = atoi(blueStr.c_str())/255.0;
	rgb result;
	result.r = redNum;
	result.g = greenNum;
	result.b = blueNum;
	return result;
}
