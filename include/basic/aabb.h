#pragma once

#include <common.h>

class aabb {
    private:
        point3 minimum, maximum;

    public:
        aabb();
        aabb(const point3 &min, const point3 &max);

        point3 min() const;
        point3 max() const;

        bool hit(const ray &r, DATA_TYPE t_min, DATA_TYPE t_max) const;

        static aabb surrounding_box(const aabb &box0, const aabb &box1);
};