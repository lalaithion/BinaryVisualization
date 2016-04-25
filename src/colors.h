#ifndef COLORS_H
#define COLORS_H

/**
 * This file contains the gradient shaders that are loaded by BV_Viewer and passed to the fragment shader to color the image
 */

extern std::string rainbow =
        "\"Rainbow\"\n"
        "use hsv\n"
        "0.0->#000001\n"
        "0.4->#0000FF\n"
        "0.6->#00CC00\n"
        "0.8->#FF0000\n"
        "1.0->#FF9999\n";

extern std::string heatmap =
        "\"Heatmap\"\n"
        "use hsv\n"
        "0.0->#000001\n"
        "0.5->#FF0000\n"
        "0.75->#FFFF00\n"
        "1.0->#FFFFFF\n";

extern std::string green =
        "\"Green\"\n"
        "use hsv\n"
        "0.0->#000001\n"
        "1.0->#00FF00\n";

extern std::string grayscale =
        "\"Grayscale\"\n"
        "use hsv\n"
        "0.0->#000000\n"
        "1.0->#FFFFFF\n";

extern std::vector<std::string> colors = {heatmap, rainbow, green, grayscale};

#endif /// COLORS_H
