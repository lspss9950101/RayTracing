#include <ray.h>

ray::ray() {}

ray::ray(const point3 &origin, const vec3 &direction, const DATA_TYPE time) : orig(origin), dir(direction), t(time) {}

point3 ray::origin() const {
    return orig;
}

vec3 ray::direction() const {
    return dir;
}

point3 ray::at(DATA_TYPE t) const {
    return orig + t*dir;
}

DATA_TYPE ray::time() const {
    return t;
}