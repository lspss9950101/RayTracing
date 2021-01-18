#include <isotropic.h>

isotropic::isotropic(color albedo) : albedo(make_shared<solid_color>(albedo)) {}

isotropic::isotropic(shared_ptr<texture> albedo) : albedo(albedo) {}

bool isotropic::scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &r_out) const {
    r_out = ray(rec.p, vec3::random_in_unit_sphere(), r_in.time());
    attenuation = albedo->value(rec.u, rec.v, rec.p);
    return true;
}