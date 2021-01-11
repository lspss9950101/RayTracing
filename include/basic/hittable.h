#pragma once

#include <common.h>

class material;

struct hit_record {
    point3 p;
    vec3 normal;
    shared_ptr<material> mat_ptr;
    DATA_TYPE t;

    bool hit_front_face;

    inline void set_normal(const ray &r, const vec3 &outward_normal) {
        hit_front_face = (dot(r.direction(), outward_normal) < 0);
        normal = hit_front_face ? outward_normal : -outward_normal;
    }
};

class hittable {
    public:
        virtual bool hit(const ray &r, DATA_TYPE t_min, DATA_TYPE t_max, hit_record &rec) const = 0;
};