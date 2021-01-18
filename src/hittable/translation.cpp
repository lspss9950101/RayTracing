#include <translation.h>

translation::translation() {}

translation::translation(shared_ptr<hittable> child, const vec3 &displacement) : child(child), offset(displacement) {}

bool translation::hit(const ray &r_in, DATA_TYPE t_min, DATA_TYPE t_max, hit_record &rec) const {
    ray translated(r_in.origin() - offset, r_in.direction(), r_in.time());
    if(!child->hit(translated, t_min, t_max, rec)) return false;

    rec.p += offset;
    rec.set_normal(translated, rec.normal);
    return true;
}

bool translation::bounding_box(DATA_TYPE time0, DATA_TYPE time1, aabb &output_box) const {
    if(!child->bounding_box(time0, time1, output_box)) return false;

    output_box = aabb(output_box.min() + offset, output_box.max() + offset);

    return true;
}