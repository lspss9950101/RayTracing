#include <noise_texture.h>

noise_texture::noise_texture() {}

noise_texture::noise_texture(DATA_TYPE scale, color c) : scale(scale), c(c) {}

color noise_texture::value(DATA_TYPE u, DATA_TYPE v, const point3 &p) const {
    return c * 0.5 * (1 + sin(scale*p[2] + 10 * noise.turb(p)));
}