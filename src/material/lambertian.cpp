#include <lambertian.h>

lambertian::lambertian(const color &albedo) : albedo(albedo) {}

bool lambertian::scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &r_out) const {
    vec3 scatter_dir = rec.normal + vec3::random_on_unit_sphere();

    if(scatter_dir.near_zero()) scatter_dir = rec.normal;

    r_out = ray(rec.p, scatter_dir);
    attenuation = albedo;
    return true;
}