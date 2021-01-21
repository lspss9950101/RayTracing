#include <hittable_pdf.h>

hittable_pdf::hittable_pdf(shared_ptr<hittable> ptr, const point3 &origin) : ptr(ptr), origin(origin) {}

DATA_TYPE hittable_pdf::value(const vec3 &dir) const {
    return ptr->pdf_value(origin, dir);
}

vec3 hittable_pdf::generate() const {
    return ptr->random(origin);
}