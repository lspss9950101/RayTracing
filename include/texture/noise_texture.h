#pragma once

#include <basic/perlin.h>
#include <basic/texture.h>

class noise_texture : public texture {
    private:
        perlin noise;
        DATA_TYPE scale;
        color c;

    public:
        noise_texture();
        noise_texture(DATA_TYPE scale, color c);

        virtual color value(DATA_TYPE u, DATA_TYPE v, const point3 &p) const override;
};