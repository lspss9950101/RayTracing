#pragma once

#include <basic/common.h>
#include <hittable/rect.h>
#include <hittable/hittable_list.h>

class aabox : public hittable {
    private:
        point3 box_min;
        point3 box_max;
        hittable_list faces;

    public:
        aabox();
        aabox(const point3 &box_min, const point3 &box_max, shared_ptr<material> mat_ptr);

        virtual bool hit(const ray &r_in, DATA_TYPE t_min, DATA_TYPE t_max, hit_record &rec) const override;

        virtual bool bounding_box(DATA_TYPE time0, DATA_TYPE time1, aabb &output_box) const override;
};