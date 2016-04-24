#ifndef COLORS_H
#define COLORS_H

extern std::string rainbow =
        "\"Rainbow\"\n"
        "usehsv\n"
        "0.0->#000001\n"
        "0.25->#000099\n"
        "0.5->#009900\n"
        "0.75->#EE0000\n"
        "1.0->#FFFFFF\n";

extern std::string heatmap =
        "\"Heatmap\"\n"
        "usehsv\n"
        "0.0->#000001\n"
        "0.5->#990099\n"
        "1.0->#FFFF00\n";

extern std::string green =
        "\"Green\"\n"
        "usehsv\n"
        "0.0->#000001\n"
        "0.5->#00FF00\n";

extern std::vector<std::string> colors = {green, rainbow, heatmap};

#endif // COLORS_H
