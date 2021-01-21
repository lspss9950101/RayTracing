#include <solid_color.h>

solid_color::solid_color() {}

solid_color::solid_color(color c) : color_value(c) {}

solid_color::solid_color(DATA_TYPE r, DATA_TYPE g, DATA_TYPE b) : color_value({r, g, b}) {}

color solid_color::value(DATA_TYPE, DATA_TYPE, const point3&) const {
    return color_value;
}