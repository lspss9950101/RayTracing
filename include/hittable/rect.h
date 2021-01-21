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
        static const int _axis2 = 3 - _axis0 - _axis1;
        vec3(*normal_function)(const point3 &p);
        static vec3 default_normal_function(const point3 &p);

    public:
        aarect();
        aarect(DATA_TYPE x0, DATA_TYPE x1, DATA_TYPE y0, DATA_TYPE y1, DATA_TYPE k, shared_ptr<material> mat_ptr);
        aarect(DATA_TYPE x0, DATA_TYPE x1, DATA_TYPE y0, DATA_TYPE y1, DATA_TYPE k, shared_ptr<material> mat_ptr, vec3(*normal_function)(const point3 &p));

        virtual bool hit(const ray &r, DATA_TYPE t_min, DATA_TYPE t_max, hit_record &rec) const override;
        virtual bool bounding_box(DATA_TYPE time0, DATA_TYPE time1, aabb &output_box) const override;
        virtual DATA_TYPE pdf_value(const point3 &origin, const vec3 &dir) const override;
        virtual vec3 random(const point3 &origin) const override;
};

#include <hittable/rect.tpp>