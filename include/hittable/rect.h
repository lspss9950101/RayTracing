#pragma once

#include <basic/common.h>
#include <basic/hittable.h>

template<int _axis0, int _axis1>
class aarect : public hittable {
    static_assert(_axis0 >= 0 && _axis0 < 3);
    static_assert(_axis1 >= 0 && _axis1 < 3);
    static_assert(_axis0 != _axis1);
    static_assert(_axis0 + _axis1 >= 1 && _axis0 + _axis1 <= 3);

    private:
        DATA_TYPE x0, x1, y0, y1, k;
        shared_ptr<material> mat_ptr;
        int _axis2;

    public:
        aarect();
        aarect(DATA_TYPE x0, DATA_TYPE x1, DATA_TYPE y0, DATA_TYPE y1, DATA_TYPE k, shared_ptr<material> mat_ptr);

        virtual bool hit(const ray &r, DATA_TYPE t_min, DATA_TYPE t_max, hit_record &rec) const override;
        virtual bool bounding_box(DATA_TYPE time0, DATA_TYPE time1, aabb &output_box) const override;
};

#include <hittable/rect.tpp>