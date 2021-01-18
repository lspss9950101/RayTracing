template<int _axis0, int _axis1>
aarect<_axis0, _axis1>::aarect() {}

template<int _axis0, int _axis1>
aarect<_axis0, _axis1>::aarect(DATA_TYPE x0, DATA_TYPE x1, DATA_TYPE y0, DATA_TYPE y1, DATA_TYPE k, shared_ptr<material> mat_ptr) :
    x0(x0), x1(x1), y0(y0), y1(y1), k(k), mat_ptr(mat_ptr), _axis2(3 - _axis0 - _axis1) {};

template<int _axis0, int _axis1>
bool aarect<_axis0, _axis1>::hit(const ray &r, DATA_TYPE t_min, DATA_TYPE t_max, hit_record &rec) const {
    auto t = (k - r.origin()[_axis2]) / r.direction()[_axis2];
    if(t < t_min || t > t_max) return false;

    auto x = r.origin()[_axis0] + t * r.direction()[_axis0];
    auto y = r.origin()[_axis1] + t * r.direction()[_axis1];
    if(x < x0 || x > x1 || y < y0 || y > y1) return false;

    rec.u = (x-x0) / (x1-x0);
    rec.v = (y-y0) / (y1-y0);
    rec.t = t;

    vec3 outward_normal({0, 0, 0});
    outward_normal[_axis2] = 1;
    rec.set_normal(r, outward_normal);
    rec.mat_ptr = mat_ptr;
    rec.p = r.at(t);
    return true;
}

template<int _axis0, int _axis1>
bool aarect<_axis0, _axis1>::bounding_box(DATA_TYPE, DATA_TYPE, aabb &output_box) const {
    point3 min, max;
    min[_axis0] = x0;
    min[_axis1] = y0;
    min[_axis2] = k-0.0001;
    max[_axis0] = x1;
    max[_axis1] = y1;
    max[_axis2] = k+0.0001;
    output_box = aabb(min, max);
    return true;
}