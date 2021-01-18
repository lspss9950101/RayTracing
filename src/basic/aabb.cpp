#include <aabb.h>

aabb::aabb() : minimum({common::inf, common::inf, common::inf}), maximum({-common::inf, -common::inf, -common::inf}) {}

aabb::aabb(const point3 &min, const point3 &max) : minimum(min), maximum(max) {};

point3 aabb::min() const {
    return minimum;
}

point3 aabb::max() const {
    return maximum;
}

bool aabb::hit(const ray &r, DATA_TYPE t_min, DATA_TYPE t_max) const {
    for(int i = 0; i < 3; i++) {
        auto invD = 1.f / r.direction()[i];
        auto t0 = (minimum[i] - r.origin()[i]) * invD;
        auto t1 = (maximum[i] - r.origin()[i]) * invD;

        if(invD < 0.f) std::swap(t0, t1);

        t_min = t0 > t_min ? t0 : t_min;
        t_max = t1 < t_max ? t1 : t_max;
        if(t_max <= t_min) return false;
    }
    return true;
}

aabb aabb::surrounding_box(const aabb &box0, const aabb &box1) {
    point3 min({
        fmin(box0.minimum[0], box1.minimum[0]),
        fmin(box0.minimum[1], box1.minimum[1]),
        fmin(box0.minimum[2], box1.minimum[2])
    });
    point3 max({
        fmax(box0.maximum[0], box1.maximum[0]),
        fmax(box0.maximum[1], box1.maximum[1]),
        fmax(box0.maximum[2], box1.maximum[2])
    });

    return aabb(min, max);
}