#pragma once

#include <basic/hittable.h>

class plane : public hittable {
    private:
        point3 origin;
        vec3 normal;
        shared_ptr<material> mat_ptr;

    public:
        plane();
        plane(point3 origin, vec3 normal, shared_ptr<material> mat_ptr);

        virtual bool hit(const ray &r, DATA_TYPE t_min, DATA_TYPE t_max, hit_record &rec) const override;
};