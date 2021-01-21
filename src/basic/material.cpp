#include <material.h>

bool material::scatter(const ray&, const hit_record&, scatter_record&) const {
    return false;
}

DATA_TYPE material::scattering_pdf(const ray&, const hit_record&, const ray&) const {
    return 0;
}

color material::emitted(const ray&, const hit_record&, DATA_TYPE, DATA_TYPE, const point3&) const {
    return color({0, 0, 0});
}