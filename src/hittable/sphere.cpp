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
    get_uv(outward_normal, rec.u, rec.v);
    rec.mat_ptr = mat_ptr;

    return true;
}

bool sphere::bounding_box(DATA_TYPE time0, DATA_TYPE time1, aabb &output_box) const {
    output_box = aabb(
        center - vec3({radius, radius, radius}),
        center + vec3({radius, radius, radius})
    );
    return true;
}

void sphere::get_uv(const point3 &p, DATA_TYPE &u, DATA_TYPE &v) {
    auto theta = acos(-p[1]);
    auto phi = atan2(-p[2], p[0]) + common::pi;

    u = phi / (2 * common::pi);
    v = theta / common::pi;
}