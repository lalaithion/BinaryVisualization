/**
 * \class Gradient
 *
 * \brief Gradient for Shaders
 * This is an interpreter that converts a short script into an OpenGL ready array of * floats. It takes a script and converts them into a readable format with a script  * of Izaak's design. Uses interpolation. 



#ifndef GRADIENT_H
#define GRADIENT_H

#include <string>
#include <vector>

#include "interpolate.h"

class Gradient
{
private:
	///private variables
    /** This vector holds point structs, which hold:
     * - a 'location' float between 0 and 1,
     * - an rgb struct, which holds:
     *  - three floats between 0 and 1
     */
	std::vector<point> colorCurve;
    /// This holds the name of the Gradient, aka the label that shows up in the dropdown.
     
	std::string name;
    /// This is a boolean that records whether this gradient uses RGB or HSV interpolation 
	bool polar;
	///private helper functions
    /// This parses the settings line of the gradient script 
	bool parseSettings(std::string);
    /// This parses the name line of the gradient script 
	std::string parseName(std::string);
    /** This parses the other lines of the gradient script
     * It calls the parseLoc and parseColor functions
     */
	point parseData(std::string);
    /// This parses the first half of the data lines of the script
     
	double parseLoc(std::string);
    /** This function parses the second half of the data lines of the script
     * By either calling parseHex or parseTup
     */
	rgb parseColor(std::string);
    /// This parses the color if it is a 6 digit hex string 
	rgb parseHex(std::string);
    /// This parses the color if it is a tuple with 3 values between 0 and 255 
	rgb parseTup(std::string);
    /// This is a short function that sorts point structs by their location float 
	static bool pointSort (point,point); 
public:
	/** \brief constructor */
    /// This is the constructor. You pass it the string that holds a script. 
	Gradient(std::string);
	///accessor functions
    /// This fills the array at the float pointer with 255 colors 
	void getTexture(float*);
    /* This returns the name of the Gradient */
	std::string getName();
};


#endif
