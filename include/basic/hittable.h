#pragma once

#include <common.h>
#include <aabb.h>

class material;

struct hit_record {
    point3 p;
    vec3 normal;
    shared_ptr<material> mat_ptr;
    DATA_TYPE t;
    DATA_TYPE u;
    DATA_TYPE v;

    bool hit_front_face;

    inline void set_normal(const ray &r, const vec3 &outward_normal) {
        hit_front_face = (dot(r.direction(), outward_normal) < 0);
        normal = hit_front_face ? outward_normal : -outward_normal;
    }
};

class hittable {
    public:
        virtual bool hit(const ray &r, DATA_TYPE t_min, DATA_TYPE t_max, hit_record &rec) const = 0;
        virtual bool bounding_box(DATA_TYPE time0, DATA_TYPE time1, aabb &output_box) const = 0;
        virtual DATA_TYPE pdf_value(const point3 &origin, const vec3 &dir) const;
        virtual vec3 random(const vec3 &origin) const;
};