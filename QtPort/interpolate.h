#ifndef INTERPOLATE_H
#define INTERPOLATE_H

typedef struct {
    double r;       // percent
    double g;       // percent
    double b;       // percent
} rgb;

typedef struct {
    double h;       // angle in degrees
    double s;       // percent
    double v;       // percent
} hsv;

typedef struct
{
	double position;// position from 0 to 1
	rgb color;      // rgb struct
} point;

const char * printcolor(rgb c);

const char * printcolor(hsv c);


//converts a rgb struct to an hsv struct
hsv rgb2hsv(rgb in);

//converts a hsv struct to an rgb struct
rgb hsv2rgb(hsv in);

//returns an rgb value for a position between two points
rgb interpolate(double current, point start, point end, std::string mode);

#endif