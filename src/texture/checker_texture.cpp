#include <checker_texture.h>

checker_texture::checker_texture() {}

checker_texture::checker_texture(shared_ptr<texture> odd, shared_ptr<texture> even) : odd(odd), even(even) {}

checker_texture::checker_texture(color odd, color even) : odd(make_shared<solid_color>(odd)), even(make_shared<solid_color>(even)) {}

color checker_texture::value(DATA_TYPE u, DATA_TYPE v, const point3 &p) const {
    auto sine = sin(10 * p[0]) * sin(10 * p[1]) * sin(10 * p[2]);
    return sine < 0 ? odd->value(u, v, p) : even->value(u, v, p);
}