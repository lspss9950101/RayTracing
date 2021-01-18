#pragma once

#include <common.h>
#include <hittable.h>

class material {
    public:
        virtual color emitted(DATA_TYPE u, DATA_TYPE v, const point3 &p) const;
        virtual bool scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &r_out) const = 0;
};