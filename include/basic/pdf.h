#pragma once

#include <common.h>

class pdf {
    public:
        virtual DATA_TYPE value(const vec3 &dir) const = 0;
        virtual vec3 generate() const = 0;
};