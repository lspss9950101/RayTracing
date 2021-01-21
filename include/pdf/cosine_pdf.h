#pragma once

#include <basic/common.h>
#include <basic/pdf.h>
#include <basic/onb.h>

class cosine_pdf : public pdf {
    private:
        onb basis;

    public:
        cosine_pdf(const vec3 &w);

        virtual DATA_TYPE value(const vec3 &dir) const override;

        virtual vec3 generate() const override;
};