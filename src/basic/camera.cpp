#include <camera.h>

camera::camera(point3 lookfrom, point3 lookat, vec3 vup, DATA_TYPE vfov, DATA_TYPE aspect_ratio, DATA_TYPE aperture, DATA_TYPE focus_dist) : origin(lookfrom) {
    auto theta = common::d2r(vfov);
    auto h = tan(theta/2);
    auto viewport_height = 2 * h;
    auto viewport_width = aspect_ratio * viewport_height;

    w = (lookfrom - lookat).unit();
    u = cross(vup, w).unit();
    v = cross(w, u);

    horizontal = focus_dist * viewport_width * u;
    vertical = focus_dist * viewport_height * v; 
    lower_left_corner = origin - horizontal/2 - vertical/2 - focus_dist * w;

    lens_radius = aperture / 2;
}

ray camera::get_ray(DATA_TYPE s, DATA_TYPE t) const {
    vec3 rd = lens_radius * vec3::random_in_unit_disk();
    vec3 offset = u * rd[0] + v * rd[1];

    return ray(origin + offset, lower_left_corner + s*horizontal + t*vertical - origin - offset);
}