#include <dielectric.h>

dielectric::dielectric(const DATA_TYPE index_of_refraction) : index_of_refraction(index_of_refraction) {}

bool dielectric::scatter(const ray &r_in, const hit_record &rec, scatter_record &srec) const {
    srec.is_specular = true;
    srec.pdf_ptr = NULL;
    srec.attenuation = color({1,1,1});
    auto relative_index_of_refraction = rec.hit_front_face ? (1 / index_of_refraction) : index_of_refraction;

    vec3 unit_dir = r_in.direction().unit();
    auto cos_theta = fmin(dot(-unit_dir, rec.normal), 1.0);
    auto sin_theta = sqrt(1 - cos_theta);

    vec3 dir_o;
    if(relative_index_of_refraction * sin_theta > 1 || reflectance(cos_theta, relative_index_of_refraction) > common::random())
        dir_o = vec3::reflect(unit_dir, rec.normal);
    else
        dir_o = vec3::refract(unit_dir, rec.normal, relative_index_of_refraction);

    srec.specular_ray = ray(rec.p, dir_o, r_in.time());
    return true;
}

DATA_TYPE dielectric::reflectance(DATA_TYPE cos_theta, DATA_TYPE ref_idx) {
    auto r0 = (1-ref_idx) / (1+ref_idx);
    r0 = r0*r0;
    return r0 + (1-r0) * pow((1-cos_theta), 5);
}