#pragma once

#include <basic/common.h>
#include <basic/material.h>

class lambertian : public material {
    private:
        color albedo;

    public:
        lambertian(const color &albedo);

        virtual bool scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &r_out) const override;
};