#include <material.h>

color material::emitted(DATA_TYPE u, DATA_TYPE v, const point3 &p) const {
    return color({0, 0, 0});
}