#pragma once

#include <vec.h>
#include <utils.h>

class ray {
    private:
        point3 orig;
        vec3 dir;
        DATA_TYPE t;

    public:
        ray();
        ray(const point3 &origin, const vec3 &direction, DATA_TYPE time);
        
        point3 origin() const;
        vec3 direction() const;
        DATA_TYPE time() const;
        
        point3 at(DATA_TYPE d) const;
};