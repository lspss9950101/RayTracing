#include <metal.h>

metal::metal(const color &albedo, const DATA_TYPE fuzziness) : albedo(albedo), fuzziness(common::clamp(fuzziness, 0, 1)) {}

bool metal::scatter(const ray &r_in, const hit_record &rec, scatter_record &srec) const {
    vec3 reflected = vec3::reflect(r_in.direction().unit(), rec.normal);
    srec.specular_ray = ray(rec.p, reflected + vec3::random_in_unit_sphere() * fuzziness, r_in.time());
    srec.attenuation = albedo;
    srec.is_specular = true;
    srec.pdf_ptr = NULL;
    
    return true;
}