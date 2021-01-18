#pragma once

#include <basic/common.h>
#include <basic/hittable.h>
#include <hittable/hittable_list.h>
#include <algorithm>

class bvh_node : public hittable {
    private:
        shared_ptr<hittable> left;
        shared_ptr<hittable> right;
        aabb box;

        template<int axis>
        static bool box_compare(const shared_ptr<hittable> a, const shared_ptr<hittable> b);

    public:
        bvh_node();
        bvh_node(hittable_list &list, DATA_TYPE time0, DATA_TYPE time1);
        bvh_node(const std::vector<shared_ptr<hittable>> &src, size_t start, size_t end, DATA_TYPE time0, DATA_TYPE time1);

        virtual bool hit(const ray &r, DATA_TYPE t_min, DATA_TYPE t_max, hit_record &rec) const override;
        virtual bool bounding_box(DATA_TYPE time0, DATA_TYPE time1, aabb &output_box) const override;
};