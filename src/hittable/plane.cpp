#include <plane.h>

plane::plane() {}

plane::plane(point3 origin, vec3 normal, shared_ptr<material> mat_ptr) : mat_ptr(mat_ptr) {
    this->normal = normal.unit();
    this->origin = this->normal * origin;
}

bool plane::hit(const ray &r, DATA_TYPE t_min, DATA_TYPE t_max, hit_record &rec) const {
    if(dot(r.direction(), normal) == 0) return false;
    
    auto c = origin[0] / normal[0];

    auto root = (c - r.origin()[0]) / normal[0];

    rec.t = root;
    rec.p = r.at(root);
    rec.set_normal(r, normal);
    rec.mat_ptr = mat_ptr;

    return true;
}