#pragma once

#include <basic/common.h>
#include <basic/hittable.h>

class translation : public hittable {
    private:
        shared_ptr<hittable> child;
        vec3 offset;

    public:
        translation();
        translation(shared_ptr<hittable> child, const vec3 &displacement);

        virtual bool hit(const ray &r_in, DATA_TYPE t_min, DATA_TYPE t_max, hit_record &rec) const override;

        virtual bool bounding_box(DATA_TYPE time0, DATA_TYPE time1, aabb &output_box) const override;
};