#pragma once

#include <common.h>

class onb {
    private:
        vec3 axis[3];

    public:
        onb();
        onb(const vec3 &w);

        inline vec3 operator[](int i) const { return axis[i]; }

        vec3 local(DATA_TYPE a, DATA_TYPE b, DATA_TYPE c) const;
        vec3 local(const vec3 &a) const;
};