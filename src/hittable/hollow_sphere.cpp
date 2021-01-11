#include <hollow_sphere.h>

hollow_sphere::hollow_sphere() : outer(point3({0, 0, 0}), 0, NULL), inner(point3({0, 0, 0}), 0, NULL) {}

hollow_sphere::hollow_sphere(point3 center, DATA_TYPE radius, DATA_TYPE thickness, shared_ptr<material> mat_ptr) : outer(center, radius, mat_ptr), inner(center, thickness - radius, mat_ptr) {}

bool hollow_sphere::hit(const ray &r, DATA_TYPE t_min, DATA_TYPE t_max, hit_record &rec) const {
    hit_record tmp_rec;
    bool hit_something = false;
    auto closest_t = t_max;

    if(outer.hit(r, t_min, closest_t, tmp_rec)) {
        hit_something = true;
        closest_t = tmp_rec.t;
        rec = tmp_rec;
    }

    if(inner.hit(r, t_min, closest_t, tmp_rec)) {
        hit_something = true;
        closest_t = tmp_rec.t;
        rec = tmp_rec;
    }

    return hit_something;
}