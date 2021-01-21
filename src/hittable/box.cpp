#include <box.h>

aabox::aabox() {}

aabox::aabox(const point3 &box_min, const point3 &box_max, shared_ptr<material> mat_ptr) : box_min(box_min), box_max(box_max) {
    faces.add(make_shared<aarect<0, 1>>(box_min[0], box_max[0], box_min[1], box_max[1], box_min[2], mat_ptr));
    faces.add(make_shared<aarect<0, 1>>(box_min[0], box_max[0], box_min[1], box_max[1], box_max[2], mat_ptr));

    faces.add(make_shared<aarect<0, 2>>(box_min[0], box_max[0], box_min[2], box_max[2], box_min[1], mat_ptr));
    faces.add(make_shared<aarect<0, 2>>(box_min[0], box_max[0], box_min[2], box_max[2], box_max[1], mat_ptr));

    faces.add(make_shared<aarect<1, 2>>(box_min[1], box_max[1], box_min[2], box_max[2], box_min[0], mat_ptr));
    faces.add(make_shared<aarect<1, 2>>(box_min[1], box_max[1], box_min[2], box_max[2], box_max[0], mat_ptr));
}

bool aabox::hit(const ray &r_in, DATA_TYPE t_min, DATA_TYPE t_max, hit_record &rec) const {
    return faces.hit(r_in, t_min, t_max, rec);
}

bool aabox::bounding_box(DATA_TYPE, DATA_TYPE, aabb &output_box) const {
    output_box = aabb(box_min, box_max);
    return true;
}