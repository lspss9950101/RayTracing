#include <cosine_pdf.h>

cosine_pdf::cosine_pdf(const vec3 &w) : basis(w) {}

DATA_TYPE cosine_pdf::value(const vec3 &dir) const {
    auto cosine = dot(dir.unit(), basis[2]);
    return cosine < 0 ? 0 : cosine / common::pi;
}

vec3 cosine_pdf::generate() const {
    return basis.local(vec3::random_cosine_dir());
}