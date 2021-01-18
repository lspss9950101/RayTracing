#pragma once

#include <basic/common.h>
#include <basic/hittable.h>
#include <basic/material.h>
#include <basic/texture.h>
#include <material/isotropic.h>

class constant_medium : public hittable {
    private:
        shared_ptr<hittable> boundary;
        DATA_TYPE neg_inv_density;
        shared_ptr<material> phase_function;

    public:
        constant_medium(shared_ptr<hittable> boundary, DATA_TYPE density, shared_ptr<texture> albedo);
        constant_medium(shared_ptr<hittable> boundary, DATA_TYPE density, color albedo);

        virtual bool hit(const ray &r, DATA_TYPE t_min, DATA_TYPE t_max, hit_record &rec) const override;
        virtual bool bounding_box(DATA_TYPE time0, DATA_TYPE time1, aabb &output_box) const override;
};