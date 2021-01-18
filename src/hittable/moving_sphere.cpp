#include <moving_sphere.h>

moving_sphere::moving_sphere() : center_begin({0, 0, 0}), center_end({0, 0, 0}), radius(0) {}

moving_sphere::moving_sphere(point3 center_begin, point3 center_end, DATA_TYPE time_begin, DATA_TYPE time_end, DATA_TYPE radius, shared_ptr<material> mat_ptr)
        : center_begin(center_begin), center_end(center_end), time_begin(time_begin), time_end(time_end), radius(radius), mat_ptr(mat_ptr) {}

bool moving_sphere::hit(const ray &r, DATA_TYPE t_min, DATA_TYPE t_max, hit_record &rec) const {
    vec3 center2ray = r.origin() - center(r.time());
    auto a = r.direction().length_squared();
    auto b_half = dot(center2ray, r.direction());
    auto c = center2ray.length_squared() - radius*radius;

    auto discriminant = b_half*b_half - a*c;
    if(discriminant < 0) return false;

    auto discriminant_sqrt = sqrt(discriminant);
    auto root = (-b_half - discriminant_sqrt) / a;
    if(root > t_max) return false;
    else if(root < t_min) {
        root = (-b_half + discriminant_sqrt) / a;
        if(root < t_min || root > t_max) return false;
    }

    rec.t = root;
    rec.p = r.at(root);
    vec3 outward_normal = (rec.p - center(r.time())) / radius;
    rec.set_normal(r, outward_normal);
    rec.mat_ptr = mat_ptr;

    return true;
}

bool moving_sphere::bounding_box(DATA_TYPE time0, DATA_TYPE time1, aabb &output_box) const {
    aabb box0(
        center(time0) - vec3({radius, radius, radius}),
        center(time0) + vec3({radius, radius, radius})
    );
    aabb box1(
        center(time1) - vec3({radius, radius, radius}),
        center(time1) + vec3({radius, radius, radius})
    );
    output_box = aabb::surrounding_box(box0, box1);
    return true;
}

point3 moving_sphere::center(DATA_TYPE time) const {
    return interpolate((time - time_begin) / (time_end - time_begin), center_begin, center_end);
}