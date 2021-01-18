#include <hittable/rotation.h>
template<int _axis>
rotation<_axis>::rotation() {}

template<int _axis>
rotation<_axis>::rotation(shared_ptr<hittable> child, DATA_TYPE angle) : child(child) {
    auto radians = common::d2r(angle);
    sin_theta = sin(radians);
    cos_theta = cos(radians);
    has_box = child->bounding_box(0, 1, box);

    point3 min({common::inf, common::inf, common::inf});
    point3 max({-common::inf, -common::inf, -common::inf});

    point3 tmp[] = {
        point3({box.min()[0], box.min()[1], box.min()[2]}),
        point3({box.min()[0], box.min()[1], box.max()[2]}),
        point3({box.min()[0], box.max()[1], box.min()[2]}),
        point3({box.min()[0], box.max()[1], box.max()[2]}),
        point3({box.max()[0], box.min()[1], box.min()[2]}),
        point3({box.max()[0], box.min()[1], box.max()[2]}),
        point3({box.max()[0], box.max()[1], box.min()[2]}),
        point3({box.max()[0], box.max()[1], box.max()[2]})
    };
    for(int i = 0; i < 8; i++) {
        rotate(tmp[i], sin_theta, cos_theta);
        for(int j = 0; j < 3; j++) {
            min[j] = fmin(min[j], tmp[i][j]);
            max[j] = fmax(max[j], tmp[i][j]);
        }
    }

    box = aabb(min, max);
}

template<int _axis>
bool rotation<_axis>::hit(const ray &r_in, DATA_TYPE t_min, DATA_TYPE t_max, hit_record &rec) const {
    point3 origin = r_in.origin();
    vec3 dir = r_in.direction();

    rotate(origin, -sin_theta, cos_theta);
    rotate(dir, -sin_theta, cos_theta);

    ray rotated(origin, dir, r_in.time());

    if(!child->hit(rotated, t_min, t_max, rec)) return false;

    rotate(rec.p, sin_theta, cos_theta);
    rotate(rec.normal, sin_theta, cos_theta);

    rec.set_normal(rotated, rec.normal);
    return true;
}

template<int _axis>
bool rotation<_axis>::bounding_box(DATA_TYPE, DATA_TYPE, aabb &output_box) const {
    if(!has_box) return false;
    output_box = box;
    return true;
}

template<>
void rotation<0>::rotate(vec3 &vec, DATA_TYPE sin_theta, DATA_TYPE cos_theta) {
    auto y = cos_theta * vec[1] - sin_theta * vec[2];
    auto z = sin_theta * vec[1] + cos_theta * vec[2];
    vec[1] = y;
    vec[2] = z;
}

template<>
void rotation<1>::rotate(vec3 &vec, DATA_TYPE sin_theta, DATA_TYPE cos_theta) {
    auto x = cos_theta * vec[0] + sin_theta * vec[2];
    auto z = - sin_theta * vec[0] + cos_theta * vec[2];
    vec[0] = x;
    vec[2] = z;
}

template<>
void rotation<2>::rotate(vec3 &vec, DATA_TYPE sin_theta, DATA_TYPE cos_theta) {
    auto x = cos_theta * vec[0] - sin_theta * vec[1];
    auto y = sin_theta * vec[0] + cos_theta * vec[1];
    vec[0] = x;
    vec[1] = y;
}