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