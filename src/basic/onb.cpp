#include <onb.h>

onb::onb() {};

onb::onb(const vec3 &w) {
    axis[2] = w.unit();
    vec3 t = (fabs(axis[2][0]) > 0.9 ? vec3({0, 1, 0}) : vec3({1, 0, 0}));
    axis[1] = cross(axis[2], t);
    axis[0] = cross(axis[1], axis[2]);
}

vec3 onb::local(DATA_TYPE a, DATA_TYPE b, DATA_TYPE c) const {
    return a * axis[0] + b * axis[1] + c * axis[2];
}

vec3 onb::local(const vec3 &a) const {
    return a[0] * axis[0] + a[1] * axis[1] + a[2] * axis[2];
}