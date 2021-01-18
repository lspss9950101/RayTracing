#include <perlin.h>

perlin::perlin() {
    ranvec = new vec3[point_count];
    for(int i = 0; i < point_count; i++)
        ranvec[i] = vec3::random(-1, 1).unit();
    perm_x = perlin_generate_perm();
    perm_y = perlin_generate_perm();
    perm_z = perlin_generate_perm();
}

perlin::~perlin() {
    delete [] ranvec;
    delete [] perm_x;
    delete [] perm_y;
    delete [] perm_z;
}

DATA_TYPE perlin::noise(const point3 &p) const {
    DATA_TYPE u = p[0] - floor(p[0]);
    DATA_TYPE v = p[1] - floor(p[1]);
    DATA_TYPE w = p[2] - floor(p[2]);
    int i = floor(p[0]);
    int j = floor(p[1]);
    int k = floor(p[2]);
    vec3 c[2][2][2];

    for(int di = 0; di < 2; di++)
        for(int dj = 0; dj < 2; dj++)
            for(int dk = 0; dk < 2; dk++)
                c[di][dj][dk] = ranvec[
                    perm_x[(i+di) & 255] ^
                    perm_y[(j+dj) & 255] ^
                    perm_z[(k+dk) & 255]
                ];

    return perlin_interp(c, u, v, w);
}

int *perlin::perlin_generate_perm() {
    int *p = new int[point_count];

    for(int i = 0; i < perlin::point_count; i++)
        p[i] = i;

    permute(p, point_count);
    
    return p;
}

void perlin::permute(int *p, int n) {
    for(int i = n-1; i > 0; i--) {
        int target = common::random(0, i+1);
        int tmp = p[i];
        p[i] = p[target];
        p[target] = tmp;
    }
}

DATA_TYPE perlin::trilinear_interp(DATA_TYPE c[2][2][2], DATA_TYPE u, DATA_TYPE v, DATA_TYPE w) {
    DATA_TYPE accum = 0;
    for(int i = 0; i < 2; i++)
        for(int j = 0; j < 2; j++)
            for(int k = 0; k < 2; k++)
                accum += (i*u + (1-i)*(1-u)) *
                         (j*v + (1-j)*(1-v)) *
                         (k*w + (1-k)*(1-w)) *
                         c[i][j][k];
    return accum;
}

DATA_TYPE perlin::perlin_interp(vec3 c[2][2][2], DATA_TYPE u, DATA_TYPE v, DATA_TYPE w) {
    double uu = u*u*(3-2*u);
    double vv = v*v*(3-2*v);
    double ww = w*w*(3-2*w);
    double accum = 0;

    for(int i = 0; i < 2; i++)
        for(int j = 0; j < 2; j++)
            for(int k = 0; k < 2; k++) {
                vec3 weight_v({u-i, v-j, w-k});
                accum += (i*uu + (1-i)*(1-uu)) *
                         (j*vv + (1-j)*(1-vv)) *
                         (k*ww + (1-k)*(1-ww)) *
                         dot(c[i][j][k], weight_v);
            }

    return accum;
}

DATA_TYPE perlin::turb(const point3 &p, int depth) const {
    DATA_TYPE accum = 0;
    point3 tmp = p;
    DATA_TYPE weight = 1;

    for(int i = 0; i < depth; i++) {
        accum += weight * noise(tmp);
        weight *= 0.5;
        tmp *= 2;
    }
    return fabs(accum);
}