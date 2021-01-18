#pragma once

#include <common.h>
#include <hittable.h>

class camera {
    private:
        point3 origin;
        point3 lower_left_corner;
        vec3 horizontal;
        vec3 vertical;
        vec3 u, v, w;
        DATA_TYPE lens_radius;
        DATA_TYPE time_begin, time_end;

    public:
        color (*color_function)(const ray&, const color&, const hittable&, int);

        camera(point3 lookfrom, point3 lookat, vec3 vup, DATA_TYPE vfov, DATA_TYPE aspect_ratio,
                DATA_TYPE aperture, DATA_TYPE focus_dist, DATA_TYPE time_begin, DATA_TYPE time_end);

        void set_color_function(color (*ray_color)(const ray&, const color&, const hittable&, int));

        ray get_ray(DATA_TYPE s, DATA_TYPE t) const;


};