#pragma once

#include <basic/common.h>
#include <basic/pdf.h>

class mixture_pdf : public pdf {
    private:
        shared_ptr<pdf> p[2];

    public:
        mixture_pdf(shared_ptr<pdf> p0, shared_ptr<pdf> p1);

        virtual DATA_TYPE value(const vec3 &dir) const override;

        virtual vec3 generate() const override;
};