#pragma once

#include <common.h>

class texture {
    public:
        virtual color value(DATA_TYPE u, DATA_TYPE v, const point3 &p) const = 0;
};