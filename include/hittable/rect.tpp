template<int _axis0, int _axis1>
aarect<_axis0, _axis1>::aarect() {}

template<int _axis0, int _axis1>
aarect<_axis0, _axis1>::aarect(DATA_TYPE x0, DATA_TYPE x1, DATA_TYPE y0, DATA_TYPE y1, DATA_TYPE k, shared_ptr<material> mat_ptr) :
    x0(x0), x1(x1), y0(y0), y1(y1), k(k), mat_ptr(mat_ptr), normal_function(default_normal_function) {}

template<int _axis0, int _axis1>
aarect<_axis0, _axis1>::aarect(DATA_TYPE x0, DATA_TYPE x1, DATA_TYPE y0, DATA_TYPE y1, DATA_TYPE k, shared_ptr<material> mat_ptr, vec3(*normal_function)(const point3 &p)) :
    x0(x0), x1(x1), y0(y0), y1(y1), k(k), mat_ptr(mat_ptr), normal_function(normal_function) {};

template<int _axis0, int _axis1>
vec3 aarect<_axis0, _axis1>::default_normal_function(const point3&) {
    vec3 normal({0, 0, 0});
    normal[_axis2] = 1;
    return normal;
}

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
    rec.p = r.at(t);

    vec3 outward_normal = normal_function(rec.p);
    rec.set_normal(r, outward_normal);
    rec.mat_ptr = mat_ptr;
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

template<int _axis0, int _axis1>
DATA_TYPE aarect<_axis0, _axis1>::pdf_value(const point3 &origin, const vec3 &dir) const {
    hit_record rec;
    if(!this->hit(ray(origin, dir), 0.001, common::inf, rec)) return 0;

    auto area = (x1-x0) * (y1-y0);
    auto distance_squared = rec.t * rec.t * dir.length_squared();
    auto cosine = fabs(dot(dir, rec.normal) / dir.length());
    
    return distance_squared / (cosine * area);
    //return cosine == 0 ? common::max_limit : distance_squared / (cosine * area);
}

template<int _axis0, int _axis1>
vec3 aarect<_axis0, _axis1>::random(const point3 &origin) const {
    point3 random_point;
    random_point[_axis0] = common::random(x0, x1);
    random_point[_axis1] = common::random(y0, y1);
    random_point[_axis2] = k;

    vec3 ret = random_point - origin;

    return ret;
}