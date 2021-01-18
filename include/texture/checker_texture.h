#pragma once

#include <basic/common.h>
#include <basic/texture.h>
#include <texture/solid_color.h>

class checker_texture : public texture {
    private:
        shared_ptr<texture> odd, even;

    public:
        checker_texture();
        checker_texture(shared_ptr<texture> odd, shared_ptr<texture> even);
        checker_texture(color odd, color even);

        virtual color value(DATA_TYPE u, DATA_TYPE v, const point3 &p) const override;
};