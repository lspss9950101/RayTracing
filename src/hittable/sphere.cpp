#include <sphere.h>

sphere::sphere() : center({0, 0, 0}), radius(0) {}

sphere::sphere(point3 center, DATA_TYPE radius, shared_ptr<material> mat_ptr) : center(center), radius(radius), mat_ptr(mat_ptr) {}

bool sphere::hit(const ray &r, DATA_TYPE t_min, DATA_TYPE t_max, hit_record &rec) const {
    vec3 center2ray = r.origin() - center;
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
    vec3 outward_normal = (rec.p - center) / radius;
    rec.set_normal(r, outward_normal);
    rec.mat_ptr = mat_ptr;

    return true;
}