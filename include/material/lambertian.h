#pragma once

#include <basic/common.h>
#include <basic/material.h>
#include <basic/texture.h>
#include <basic/onb.h>
#include <texture/solid_color.h>
#include <pdf/cosine_pdf.h>

class lambertian : public material {
    private:
        shared_ptr<texture> albedo;

    public:
        lambertian(const color &albedo);
        lambertian(shared_ptr<texture> albedo);

        virtual bool scatter(const ray &r_in, const hit_record &rec, scatter_record &srec) const override;
        virtual DATA_TYPE scattering_pdf(const ray &r_in, const hit_record &rec, const ray &r_out) const override;
};