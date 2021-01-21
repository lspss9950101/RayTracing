#include <isotropic.h>

isotropic::isotropic(color albedo) : albedo(make_shared<solid_color>(albedo)) {}

isotropic::isotropic(shared_ptr<texture> albedo) : albedo(albedo) {}

bool isotropic::scatter(const ray &r_in, const hit_record &rec, scatter_record &srec) const {
    srec.is_specular = true;
    srec.attenuation = albedo->value(rec.u, rec.v, rec.p);
    srec.specular_ray = ray(rec.p, vec3::random_in_unit_sphere(), r_in.time());
    srec.pdf_ptr = NULL;
    return true;
}