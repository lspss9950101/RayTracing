#include <flip_face.h>

flip_face::flip_face(shared_ptr<hittable> child) : child(child) {} 

bool flip_face::hit(const ray &r, DATA_TYPE t_min, DATA_TYPE t_max, hit_record &rec) const {
    if(!child->hit(r, t_min, t_max, rec)) return false;

    rec.hit_front_face = !rec.hit_front_face;
    return true;
}

bool flip_face::bounding_box(DATA_TYPE time0, DATA_TYPE time1, aabb &output_box) const {
    return child->bounding_box(time0, time1, output_box);
}