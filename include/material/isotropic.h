#pragma once

#include <basic/common.h>
#include <basic/material.h>
#include <basic/texture.h>
#include <texture/solid_color.h>

class isotropic : public material {
    private:
        shared_ptr<texture> albedo;

    public:
        isotropic(color c);
        isotropic(shared_ptr<texture> albedo);

        virtual bool scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &r_out) const override;
};