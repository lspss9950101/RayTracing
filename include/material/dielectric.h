#pragma once

#include <basic/common.h>
#include <basic/material.h>

class dielectric : public material {
    private:
        color albedo;
        DATA_TYPE fuzziness;
        DATA_TYPE index_of_refraction;

    public:
        dielectric(const DATA_TYPE index_of_refraction);
        
        virtual bool scatter(const ray &r_in, const hit_record &rec, scatter_record &srec) const override;

    private:
        static DATA_TYPE reflectance(DATA_TYPE cos_theta, DATA_TYPE ref_idx);
};