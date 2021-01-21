#include <diffuse_light.h>

diffuse_light::diffuse_light() {}

diffuse_light::diffuse_light(shared_ptr<texture> albedo) : emit(albedo) {}

diffuse_light::diffuse_light(color albedo) : emit(make_shared<solid_color>(albedo)) {}

color diffuse_light::emitted(const ray&, const hit_record&, DATA_TYPE u, DATA_TYPE v, const point3 &p) const {
    return emit->value(u, v, p);
}