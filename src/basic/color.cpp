#include <color.h>

void write_color(std::ostream &os, color c, int samples_per_pixel) {
    DATA_TYPE s = 1.0 / samples_per_pixel;

    c = color({ sqrt(c[0]*s), sqrt(c[1]*s), sqrt(c[2]*s) });

    os << (int)(256 * common::clamp(c[0], 0, 0.999)) << ' '
       << (int)(256 * common::clamp(c[1], 0, 0.999)) << ' '
       << (int)(256 * common::clamp(c[2], 0, 0.999)) << '\n';
}