#pragma once

#include <basic/common.h>
#include <basic/hittable.h>

template<int _axis>
class rotation : public hittable {
    static_assert(_axis >= 0 && _axis < 3);

    private:
        shared_ptr<hittable> child;
        DATA_TYPE sin_theta;
        DATA_TYPE cos_theta;
        bool has_box;
        aabb box;

        static void rotate(vec3 &vec, DATA_TYPE sin_theta, DATA_TYPE cos_theta);

    public:
        rotation();
        rotation(shared_ptr<hittable> child, DATA_TYPE angle);

        virtual bool hit(const ray &r_in, DATA_TYPE t_min, DATA_TYPE t_max, hit_record &rec) const override;

        virtual bool bounding_box(DATA_TYPE time0, DATA_TYPE time1, aabb &output_box) const override;
};

#include <hittable/rotation.tpp>