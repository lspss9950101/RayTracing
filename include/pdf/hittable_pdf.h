#pragma once

#include <basic/common.h>
#include <basic/pdf.h>
#include <basic/hittable.h>

class hittable_pdf : public pdf {
    private:
        shared_ptr<hittable> ptr;
        point3 origin;

    public:
        hittable_pdf(shared_ptr<hittable> ptr, const point3 &origin);

        virtual DATA_TYPE value(const vec3 &dir) const override;

        virtual vec3 generate() const override;
};