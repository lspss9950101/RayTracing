#include <hittable_list.h>

hittable_list::hittable_list() {}

hittable_list::hittable_list(shared_ptr<hittable> obj) {
    add(obj);
}

void hittable_list::clear() {
    objs.clear();
}

void hittable_list::add(shared_ptr<hittable> obj) {
    objs.push_back(obj);
}

std::vector<shared_ptr<hittable>>& hittable_list::objects() {
    return objs;
}

bool hittable_list::hit(const ray &r, DATA_TYPE t_min, DATA_TYPE t_max, hit_record &rec) const {
    hit_record tmp_rec;
    bool hit_something = false;
    auto closest_t = t_max;

    for(const auto &obj : objs) {
        if(obj->hit(r, t_min, closest_t, tmp_rec)) {
            hit_something = true;
            closest_t = tmp_rec.t;
            rec = tmp_rec;
        }
    }

    return hit_something;
}

bool hittable_list::bounding_box(DATA_TYPE time0, DATA_TYPE time1, aabb &output_box) const {
    if(objs.empty()) return false;

    aabb tmp;
    output_box = aabb();

    for(const auto &obj : objs) {
        if(!obj->bounding_box(time0, time1, tmp)) return false;
        output_box = aabb::surrounding_box(tmp, output_box);
    }
    return true;
}

DATA_TYPE hittable_list::pdf_value(const vec3 &origin, const vec3 &dir) const {
    DATA_TYPE weight = 1.0 / objs.size();
    DATA_TYPE sum = 0;

    for(const auto &obj : objs)
        sum += weight * obj->pdf_value(origin, dir);

    return sum;
}

vec3 hittable_list::random(const vec3 &origin) const {
    return objs[common::random(0, objs.size())]->random(origin);
}