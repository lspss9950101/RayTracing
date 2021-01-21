#include <mixture_pdf.h>

mixture_pdf::mixture_pdf(shared_ptr<pdf> p0, shared_ptr<pdf> p1) {
    p[0] = p0;
    p[1] = p1;
}

DATA_TYPE mixture_pdf::value(const vec3 &dir) const {
    return 0.5 * p[0]->value(dir) + 0.5 * p[1]->value(dir);
}

vec3 mixture_pdf::generate() const {
    vec3 p0 = p[0]->generate();

    if(common::random() < 0.5 && p[0]->value(p0) < common::inf) return p0;
    else return p[1]->generate();
}