#pragma once

#include <common.h>

class perlin {
    private:
        static const int point_count = 256;
        vec3 *ranvec;
        int *perm_x;
        int *perm_y;
        int *perm_z;

        static int *perlin_generate_perm();
        static void permute(int *p, int n);
        static DATA_TYPE trilinear_interp(DATA_TYPE c[2][2][2], DATA_TYPE u, DATA_TYPE v, DATA_TYPE w);
        static DATA_TYPE perlin_interp(vec3 c[2][2][2], DATA_TYPE u, DATA_TYPE v, DATA_TYPE w);

    public:
        perlin();
        ~perlin();

        DATA_TYPE turb(const point3 &p, int depth=7) const;

        DATA_TYPE noise(const point3 &p) const;
};