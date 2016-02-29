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
	double position;
	rgb color;
} point;

hsv rgb2hsv(rgb in);
rgb hsv2rgb(hsv in);
rgb interpolate(double current, point start, point end, std::string mode = "hsv");

#endif