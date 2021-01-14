#pragma once

#include <basic/hittable.h>

class moving_sphere : public hittable {
    private:
        point3 center_begin, center_end;
        DATA_TYPE time_begin, time_end;
        DATA_TYPE radius;
        shared_ptr<material> mat_ptr;

    public:
        moving_sphere();
        moving_sphere(point3 center_begin, point3 center_end, DATA_TYPE time_begin, DATA_TYPE time_end, DATA_TYPE radius, shared_ptr<material> mat_ptr);

        virtual bool hit(const ray &r, DATA_TYPE t_min, DATA_TYPE t_max, hit_record &rec) const override;

        point3 center(DATA_TYPE time) const;
};