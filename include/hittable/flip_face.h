#pragma once

#include <basic/common.h>
#include <basic/hittable.h>

class flip_face : public hittable {
    private:
        shared_ptr<hittable> child;

    public:
        flip_face(shared_ptr<hittable> child);

        virtual bool hit(const ray &r, DATA_TYPE t_min, DATA_TYPE t_max, hit_record &rec) const override;
        virtual bool bounding_box(DATA_TYPE time0, DATA_TYPE time1, aabb &output_box) const override;
};