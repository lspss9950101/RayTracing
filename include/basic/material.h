#pragma once

#include <common.h>
#include <hittable.h>
#include <pdf.h>

struct scatter_record {
    ray specular_ray;
    bool is_specular;
    color attenuation;
    shared_ptr<pdf> pdf_ptr;
};

class material {
    public:
        virtual bool scatter(const ray &r_in, const hit_record &rec, scatter_record &srec) const;
        virtual DATA_TYPE scattering_pdf(const ray &r_in, const hit_record &rec, const ray &r_out) const;
        virtual color emitted(const ray &r_in, const hit_record &rec, DATA_TYPE u, DATA_TYPE v, const point3 &p) const;
};