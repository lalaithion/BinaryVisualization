#include <limits>
#include <string>
#include <iostream>
#include <stdio.h>
#include <cmath>

#include "interpolate.h"

const char * printcolor(rgb c)
{
    std::string result;
    result = "r=";
    result += std::to_string(c.r);
    result += ", g=";
    result += std::to_string(c.g);
    result += ", b=";
    result += std::to_string(c.b);
    return result.c_str();
}

const char * printcolor(hsv c)
{
    std::string result;
    result = "h=";
    result += std::to_string(c.h);
    result += ", s=";
    result += std::to_string(c.s);
    result += ", v=";
    result += std::to_string(c.v);
    return result.c_str();
}

// http://stackoverflow.com/questions/3018313/algorithm-to-convert-rgb-to-hsv-and-hsv-to-rgb-in-range-0-255-for-both

hsv rgb2hsv(rgb in)
{
    // local variables
    hsv         out;
    double      min, max, delta;

    // set minimum to the smallest rgb value
    min = in.r < in.g ? in.r : in.g;
    min = min  < in.b ? min  : in.b;

    // set maximum to the largest rgb value
    max = in.r > in.g ? in.r : in.g;
    max = max  > in.b ? max  : in.b;

    // the value value is the maximum rgb value
    out.v = max;

    // delta is the biggest difference in rgb values
    delta = max - min;

    
    if (delta < 0.00001)
    {
        // this means that all of the rgb values are really close
        // this happens with greys, so saturation is 0 and hue is undefined
        out.s = 0;
        out.h = 0; // FIX - UNDEFINED SHOULD NOT BE 0
        return out;
    }

    if( max > 0.0 ) 
    { 
        // if max were 0, this division would not work.
        out.s = (delta / max);
    } 
    else 
    {
        // if max is 0, then r = g = b = 0              
        // s = 0, v is undefined
        // isn't this case already handled in the first if?
        out.s = 0.0;
        out.h = std::numeric_limits<double>::quiet_NaN();
        return out;
    }

    // these if statements put hue in some weird sort of 0-6 degrees.
    if( in.r >= max )                           // > is bogus, just keeps compilor happy
    {
        // if red is the maximum, then the hue is red (0)
        // plus some if we're yellowish, or minus some if we're purplish
        out.h = ( in.g - in.b ) / delta;        // between yellow & magenta
    }
    else if( in.g >= max )
    {
        // if green is the maximum, then the hue is green (2)
        // plus some if we're cyanish, or minus some if we're yellowish
        out.h = 2.0 + ( in.b - in.r ) / delta;  // between cyan & yellow
    }
    else
    {
        // if blue is the maximum, then the hue is blue (4)
        // plus some if we're purplish, or minus some if we're cyanish
        out.h = 4.0 + ( in.r - in.g ) / delta;  // between magenta & cyan
    }

    // convert to degrees
    out.h *= 60.0;

    // this can happen if we're purplish and red is the maximum
    if( out.h < 0.0 )
    {
        out.h += 360.0;
    }

    return out;
}


rgb hsv2rgb(hsv in)
{
    // local variables
    double      hh, p, q, t, ff;
    long        i;
    rgb         out;

    if(in.s <= 0.0) {       // < is bogus, just shuts up warnings
        // if saturation is 0, this is a grey
        // the red, blue, and green are all the same
        // which is equal to the value
        out.r = in.v;
        out.g = in.v;
        out.b = in.v;
        return out;
    }

    // hh is hue transformed into the weird 0-6 measurement
    hh = in.h;
    if(hh >= 360.0) hh = 0.0;
    hh /= 60.0;

    // i is the integer part of hue, from 0 to 6
    // ff is the fractional part of hue
    i = (long)hh;
    ff = hh - i;

    // very confusing math; essentially two of the 
    // rgb components will be two of these values
    // and the last will be in.v itself
    p = in.v * (1.0 - in.s);
    q = in.v * (1.0 - (in.s * ff));
    t = in.v * (1.0 - (in.s * (1.0 - ff)));

    // these are the cases; very complex and I won't
    // comment each one because ouch
    switch(i) {
    case 0:
        out.r = in.v;
        out.g = t;
        out.b = p;
        break;
    case 1:
        out.r = q;
        out.g = in.v;
        out.b = p;
        break;
    case 2:
        out.r = p;
        out.g = in.v;
        out.b = t;
        break;
    case 3:
        out.r = p;
        out.g = q;
        out.b = in.v;
        break;
    case 4:
        out.r = t;
        out.g = p;
        out.b = in.v;
        break;
    case 5:
    default:
        out.r = in.v;
        out.g = p;
        out.b = q;
        break;
    }
    return out;     
}

// this is what I've written

rgb interpolate(double current, point start, point end, std::string mode)
{

    double percent = (current - start.position)/(end.position - start.position);

    //the following is working code. I am testing out the addition of the Luv color scheme above
    //printf("%d:", (int)polar);
    // percent is the distance between the start and end we are
    

    if((start.color.r == start.color.g) && (start.color.g == start.color.b))
    {
        //printf("%s:",printcolor(start.color));
        mode = "rgb";
    }
    else if((end.color.r == end.color.g) && (end.color.g == end.color.b))
    {
        //printf("%s:",printcolor(end.color));
        mode = "rgb";
    }
    //printf("%d\n", (int)polar);
    if (mode.compare("hsv") == 0)
    {
        hsv alpha = rgb2hsv(start.color);
        hsv beta = rgb2hsv(end.color);
        hsv result;
        double distance;
        if ((alpha.h > beta.h) && (alpha.h > 180) && (beta.h < alpha.h - 180))
        {
            distance = beta.h - (alpha.h - 360);
            result.h = alpha.h + (distance * percent);
            if(result.h > 360)
            {
                result.h -= 360;
            }
        }
        else if ((beta.h > alpha.h) && (beta.h > 180) && (alpha.h < beta.h - 180))
        {
            distance = alpha.h - (beta.h - 360);
            result.h = alpha.h - (distance * percent);
            if(result.h < 0)
            {
                result.h += 360;
            }
        }
        else
        {
            result.h = (alpha.h * (1 - percent)) + (beta.h * (percent));
        }
        result.s = (alpha.s * (1 - percent)) + (beta.s * (percent));
        result.v = (alpha.v * (1 - percent)) + (beta.v * (percent));
        rgb returnable = hsv2rgb(result);
        //printf("%f: %d, %d, %d\n",current,(int)(returnable.r*255.0),(int)(returnable.g*255.0),(int)(returnable.b*255.0));
        return returnable;
    }
    else
    {
        rgb result;
        result.r = (start.color.r * (1 - percent)) + (end.color.r * (percent));
        result.g = (start.color.g * (1 - percent)) + (end.color.g * (percent));
        result.b = (start.color.b * (1 - percent)) + (end.color.b * (percent));
        return result;
    }
    rgb error;
    return error;
}
