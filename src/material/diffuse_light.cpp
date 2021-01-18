#include <diffuse_light.h>

diffuse_light::diffuse_light() {}

diffuse_light::diffuse_light(shared_ptr<texture> albedo) : emit(albedo) {}

diffuse_light::diffuse_light(color albedo) : emit(make_shared<solid_color>(albedo)) {}

bool diffuse_light::scatter(const ray &r_in, const hit_record &rec, color &atteunation, ray &r_out) const {
    return false;
}

color diffuse_light::emitted(DATA_TYPE u, DATA_TYPE v, const point3 &p) const {
    return emit->value(u, v, p);
}