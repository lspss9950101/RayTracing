#include <lambertian.h>

lambertian::lambertian(const color &albedo) : albedo(make_shared<solid_color>(albedo)) {}

lambertian::lambertian(shared_ptr<texture> albedo) : albedo(albedo) {}

bool lambertian::scatter(const ray&, const hit_record &rec, scatter_record &srec) const {
    srec.is_specular = false;
    srec.attenuation = albedo->value(rec.u, rec.v, rec.p);
    srec.pdf_ptr = make_shared<cosine_pdf>(rec.normal);
    return true;
}

DATA_TYPE lambertian::scattering_pdf(const ray&, const hit_record &rec, const ray &r_out) const {
    auto cosine = dot(rec.normal, r_out.direction().unit());
    return cosine < 0 ? 0 : cosine / common::pi;
}
