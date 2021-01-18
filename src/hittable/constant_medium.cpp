#include <constant_medium.h>

constant_medium::constant_medium(shared_ptr<hittable> boundary, DATA_TYPE density, shared_ptr<texture> albedo)
    : boundary(boundary), neg_inv_density(-1/density), phase_function(make_shared<isotropic>(albedo)) {}

constant_medium::constant_medium(shared_ptr<hittable> boundary, DATA_TYPE density, color albedo)
    : boundary(boundary), neg_inv_density(-1/density), phase_function(make_shared<isotropic>(albedo)) {}

bool constant_medium::hit(const ray &r, DATA_TYPE t_min, DATA_TYPE t_max, hit_record &rec) const {
    const bool enableDebug = false;
    const bool debugging = enableDebug && common::random() < 0.00001;

    hit_record rec1, rec2;

    if(!boundary->hit(r, -common::inf, common::inf, rec1)) return false;
    if(!boundary->hit(r, rec1.t+0.0001, common::inf, rec2)) return false;

    if(debugging) std::cerr << "\nt_min=" << rec1.t << ", t_max=" << rec2.t << "\n";

    if(rec1.t < t_min) rec1.t = t_min;
    if(rec2.t > t_max) rec2.t = t_max;

    if(rec1.t >= rec2.t) return false;

    if(rec1.t < 0) rec1.t = 0;

    const auto ray_length = r.direction().length();
    const auto distance_in_boundary = ray_length * (rec2.t - rec1.t);
    const auto hit_distance = neg_inv_density * log(common::random());

    if(hit_distance > distance_in_boundary) return false;

    rec.t = rec1.t + hit_distance / ray_length;
    rec.p = r.at(rec.t);

    if(debugging) std::cerr << "hit_distance = " << hit_distance << '\n' << "rec.t = " << rec.t << '\n' << "rec.p = " << rec.p << '\n';

    rec.normal = vec3({1, 0, 0});
    rec.hit_front_face = true;
    rec.mat_ptr = phase_function;
    return true;
}

bool constant_medium::bounding_box(DATA_TYPE time0, DATA_TYPE time1, aabb &output_box) const {
    return boundary->bounding_box(time0, time1, output_box);
}