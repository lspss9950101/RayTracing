#include <hittable.h>

DATA_TYPE hittable::pdf_value(const point3&, const vec3&) const {
    return 0;
}

vec3 hittable::random(const vec3&) const {
    return vec3({1, 0, 0});
}