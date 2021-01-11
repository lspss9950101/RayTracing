#include <metal.h>

metal::metal(const color &albedo, const DATA_TYPE fuzziness) : albedo(albedo), fuzziness(common::clamp(fuzziness, 0, 1)) {}

bool metal::scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &r_out) const {
    vec3 reflected = vec3::reflect(r_in.direction().unit(), rec.normal);
    r_out = ray(rec.p, reflected + vec3::random_in_unit_sphere() * fuzziness);
    attenuation = albedo;
    return (dot(r_out.direction(), rec.normal) > 0);
}