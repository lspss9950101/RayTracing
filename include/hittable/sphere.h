#pragma once

#include <basic/hittable.h>
#include <basic/onb.h>

class sphere : public hittable {
    private:
        point3 center;
        DATA_TYPE radius;
        shared_ptr<material> mat_ptr;

    public:
        sphere();
        sphere(point3 center, DATA_TYPE radius, shared_ptr<material> mat_ptr);

        virtual bool hit(const ray &r, DATA_TYPE t_min, DATA_TYPE t_max, hit_record &rec) const override;
        virtual bool bounding_box(DATA_TYPE time0, DATA_TYPE time1, aabb &output_box) const override;
        virtual DATA_TYPE pdf_value(const point3 &origin, const vec3 &dir) const override;
        virtual vec3 random(const point3 &origin) const override;

        static void get_uv(const point3 &p, DATA_TYPE &u, DATA_TYPE &v);
};