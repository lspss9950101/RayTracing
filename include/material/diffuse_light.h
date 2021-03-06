#pragma once

#include <basic/common.h>
#include <basic/texture.h>
#include <basic/material.h>
#include <texture/solid_color.h>

class diffuse_light : public material {
    private:
        shared_ptr<texture> emit;

    public:
        diffuse_light();
        diffuse_light(shared_ptr<texture> albedo);
        diffuse_light(color albedo);
        
        virtual color emitted(const ray &r_in, const hit_record &rec, DATA_TYPE u, DATA_TYPE v, const point3 &p) const override;
};