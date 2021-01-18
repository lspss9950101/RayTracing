#pragma once

#include <basic/common.h>
#include <basic/texture.h>

class solid_color : public texture {
    private:
        color color_value;

    public:
        solid_color();
        solid_color(color c);
        solid_color(DATA_TYPE r, DATA_TYPE g, DATA_TYPE b);

        virtual color value(DATA_TYPE u, DATA_TYPE v, const point3 &p) const override;
};