#pragma once

#include <basic/hittable.h>
#include <hittable/sphere.h>

class hollow_sphere : public hittable {
    private:
        sphere outer;
        sphere inner;

    public:
        hollow_sphere();
        hollow_sphere(point3 center, DATA_TYPE radius, DATA_TYPE thickness, shared_ptr<material> mat_ptr);

        virtual bool hit(const ray &r, DATA_TYPE t_min, DATA_TYPE t_max, hit_record &rec) const override;
        virtual bool bounding_box(DATA_TYPE time0, DATA_TYPE time1, aabb &output_box) const override;
};