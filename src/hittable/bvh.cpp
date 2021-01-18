#include <bvh.h>

bvh_node::bvh_node() {}

bvh_node::bvh_node(hittable_list &list, DATA_TYPE time0, DATA_TYPE time1)
    : bvh_node(list.objects(), 0, list.objects().size(), time0, time1) {}

bvh_node::bvh_node(const std::vector<shared_ptr<hittable>> &src, size_t start, size_t end, DATA_TYPE time0, DATA_TYPE time1) {
    auto objects = src;
    int axis = common::random(0, 3);

    auto comparator = axis == 0 ? box_compare<0>
                    : axis == 1 ? box_compare<1>
                                : box_compare<2>;

    size_t object_number = end - start;
    if(object_number == 0) {
        left = right = NULL;
        return;
    } else if(object_number == 1) left = right = objects[start];
    else if(object_number == 2) {
        if(comparator(objects[start], objects[start+1])) {
            left = objects[start];
            right = objects[start+1];
        } else {
            left = objects[start+1];
            right = objects[start];
        }
    } else {
        std::sort(objects.begin() + start, objects.begin() + end, comparator);

        auto mid = start + object_number / 2;
        left = make_shared<bvh_node>(objects, start, mid, time0, time1);
        right = make_shared<bvh_node>(objects, mid, end, time0, time1);
    }

    aabb box_l, box_r;
    assert(left->bounding_box(time0, time1, box_l) && right->bounding_box(time0, time1, box_r));
    box = aabb::surrounding_box(box_l, box_r);
}

template<int axis>
bool bvh_node::box_compare(const shared_ptr<hittable> a, const shared_ptr<hittable> b) {
    aabb box_a, box_b;
    assert(a->bounding_box(0, 0, box_a) && b->bounding_box(0, 0, box_b));

    return box_a.min()[axis] < box_b.min()[axis];
}

bool bvh_node::hit(const ray &r, DATA_TYPE t_min, DATA_TYPE t_max, hit_record &rec) const {
    if(left == NULL || right == NULL) return false;
    if(!box.hit(r, t_min, t_max)) return false;
    bool hit_left = left->hit(r, t_min, t_max, rec);
    bool hit_right = right->hit(r, t_min, hit_left ? rec.t : t_max, rec);

    return hit_left || hit_right;
}

bool bvh_node::bounding_box(DATA_TYPE time0, DATA_TYPE time1, aabb &output_box) const {
    if(left == NULL || right == NULL) return false;
    output_box = box;
    return true;
}