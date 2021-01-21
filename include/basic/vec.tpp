#include "vec.h"

template<size_t _dim_>
vec<_dim_>::vec() {
    for(size_t i = 0; i < _dim_; i++)
        e[i] = 0;
}

template<size_t _dim_>
vec<_dim_>::vec(std::initializer_list<DATA_TYPE> d) {
    assert(d.size() == _dim_);
    std::copy(d.begin(), d.end(), e);
}

template<size_t _dim_>
inline vec<_dim_> vec<_dim_>::operator-() const {
    vec<_dim_> ret;
    for(size_t i = 0; i < _dim_; i++)
        ret[i] = -e[i];
    return ret;
}

template<size_t _dim_>
inline DATA_TYPE vec<_dim_>::operator[](int i) const {
    return e[i];
}

template<size_t _dim_>
inline DATA_TYPE& vec<_dim_>::operator[](int i) {
    return e[i];
}

template<size_t _dim_>
inline vec<_dim_>& vec<_dim_>::operator+=(const vec<_dim_> &v) {
    for(size_t i = 0; i < _dim_; i++)
        e[i] += v.e[i];
    return *this;
}

template<size_t _dim_>
inline vec<_dim_>& vec<_dim_>::operator-=(const vec<_dim_> &v) {
    for(size_t i = 0; i < _dim_; i++)
        e[i] -= v.e[i];
    return *this;
}

template<size_t _dim_>
inline vec<_dim_>& vec<_dim_>::operator*=(const vec<_dim_> &v) {
    for(size_t i = 0; i < _dim_; i++)
        e[i] *= v.e[i];
    return *this;
}

template<size_t _dim_>
inline vec<_dim_>& vec<_dim_>::operator*=(const DATA_TYPE &s) {
    for(size_t i = 0; i < _dim_; i++)
        e[i] *= s;
    return *this;
}

template<size_t _dim_>
inline vec<_dim_>& vec<_dim_>::operator/=(const vec<_dim_> &v) {
    for(size_t i = 0; i < _dim_; i++)
        e[i] /= v.e[i];
    return *this;
}

template<size_t _dim_>
inline vec<_dim_>& vec<_dim_>::operator/=(const DATA_TYPE &s) {
    DATA_TYPE ss = 1.0 / s;
    for(size_t i = 0; i < _dim_; i++)
        e[i] *= ss;
    return *this;
}

template<size_t _dim_>
inline vec<_dim_> vec<_dim_>::operator+(const vec<_dim_> &v) const {
    vec<_dim_> ret;
    for(size_t i = 0; i < _dim_; i++)
        ret.e[i] = e[i] + v.e[i];
    return ret;
}

template<size_t _dim_>
inline vec<_dim_> vec<_dim_>::operator-(const vec<_dim_> &v) const {
    vec<_dim_> ret;
    for(size_t i = 0; i < _dim_; i++)
        ret.e[i] = e[i] - v.e[i];
    return ret;
}

template<size_t _dim_>
inline vec<_dim_> vec<_dim_>::operator*(const vec<_dim_> &v) const {
    vec<_dim_> ret;
    for(size_t i = 0; i < _dim_; i++)
        ret.e[i] = e[i] * v.e[i];
    return ret;
}

template<size_t _dim_>
inline vec<_dim_> vec<_dim_>::operator*(const DATA_TYPE &s) const {
    vec<_dim_> ret;
    for(size_t i = 0; i < _dim_; i++)
        ret.e[i] = e[i] * s;
    return ret;
}

template<size_t _dim_>
inline vec<_dim_> vec<_dim_>::operator/(const vec<_dim_> &v) const {
    vec<_dim_> ret;
    for(size_t i = 0; i < _dim_; i++)
        ret.e[i] = e[i] / v.e[i];
    return ret;
}

template<size_t _dim_>
inline vec<_dim_> vec<_dim_>::operator/(const DATA_TYPE &s) const {
    vec<_dim_> ret;
    DATA_TYPE ss = 1.0 / s;
    for(size_t i = 0; i < _dim_; i++)
        ret.e[i] = e[i] * ss;
    return ret;
}

template<size_t _dim_>
inline vec<_dim_> vec<_dim_>::cross(const vec<_dim_> &v) const {
    vec<_dim_> ret;
    for(size_t i = 0; i < _dim_; i++)
        ret.e[i] = e[(i+1) % _dim_] * v.e[(i+2) % _dim_] - e[(i+2) % _dim_] * v.e[(i+1) % _dim_];
    return ret;
}

template<size_t _dim_>
inline DATA_TYPE vec<_dim_>::dot(const vec<_dim_> &v) const {
    DATA_TYPE ret = 0;
    for(size_t i = 0; i < _dim_; i++)
        ret += e[i] * v.e[i];
    return ret;
}

template<size_t _dim_>
inline DATA_TYPE vec<_dim_>::length_squared() const {
    DATA_TYPE ret = 0;
    for(size_t i = 0; i < _dim_; i++) ret += e[i]*e[i];
    return ret;
}

template<size_t _dim_>
inline DATA_TYPE vec<_dim_>::length() const {
    return sqrt(this->length_squared());
}

template<size_t _dim_>
inline vec<_dim_> vec<_dim_>::unit() const {
    return *this / this->length();
}

template<size_t _dim_>
inline bool vec<_dim_>::near_zero() const {
    const DATA_TYPE s = 1e-8;
    bool ret = true;
    for(size_t i = 0; i < _dim_; i++)
        ret = ret && (fabs(e[i]) < s);
    return ret;
}

template<size_t _dim_>
inline vec<_dim_> operator*(const DATA_TYPE &s, const vec<_dim_> &v) {
    return v*s;
}

template<size_t _dim_>
inline vec<_dim_> cross(const vec<_dim_> &v1, const vec<_dim_> &v2) {
    return v1.cross(v2);
}

template<size_t _dim_>
inline DATA_TYPE dot(const vec<_dim_> &v1, const vec<_dim_> &v2) {
    return v1.dot(v2);
}

template<size_t _dim_>
inline vec<_dim_> interpolate(const DATA_TYPE t, const vec<_dim_> &v1, const vec<_dim_> &v2) {
    return t * v2 + (1.0 - t) * v1;
}

template<size_t _dim_>
inline std::ostream& operator<<(std::ostream &os, const vec<_dim_> &v) {
    os << '(';
    for(size_t i = 0; i < _dim_; i++) {
        if(i != 0) os << ',';
        os << v[i];
    }
    os << ')';
    return os;
}

template<size_t _dim_>
inline vec<3> vec<_dim_>::random() {
    return vec<3>({common::random(), common::random(), common::random()});
}

template<size_t _dim_>
inline vec<3> vec<_dim_>::random(DATA_TYPE min, DATA_TYPE max) {
    return vec<3>({common::random(min, max), common::random(min, max), common::random(min, max)});
}

template<size_t _dim_>
inline vec<3> vec<_dim_>::random_in_unit_sphere() {
    while(true) {
        vec<3> p = vec<3>::random(-1, 1);
        if(p.length_squared() < 1) return p;
    }
}

template<size_t _dim_>
inline vec<3> vec<_dim_>::random_on_unit_sphere() {
    return vec<_dim_>::random_in_unit_sphere().unit();
}

template<size_t _dim_>
inline vec<3> vec<_dim_>::random_in_unit_disk() {
    while(true) {
        vec<3> p({common::random(-1, 1), common::random(-1, 1), 0});
        if(p.length_squared() < 1) return p;
    }
}

template<size_t _dim_>
inline vec<3> vec<_dim_>::random_cosine_dir() {
    DATA_TYPE r1 = common::random();
    DATA_TYPE r2 = common::random();
    DATA_TYPE z = sqrt(1 - r2);
    DATA_TYPE phi = 2 * common::pi * r1;
    DATA_TYPE x = cos(phi) * sqrt(r2);
    DATA_TYPE y = sin(phi) * sqrt(r2);

    return vec3({x, y, z});
}

template<size_t _dim_>
inline vec<3> vec<_dim_>::random_to_sphere(DATA_TYPE radius, DATA_TYPE distance_squared) {
    DATA_TYPE r1 = common::random();
    DATA_TYPE r2 = common::random();
    DATA_TYPE z = 1 + r2*(sqrt(1-radius*radius/distance_squared) - 1);

    DATA_TYPE phi = 2*common::pi*r1;
    DATA_TYPE x = cos(phi)*sqrt(1-z*z);
    DATA_TYPE y = sin(phi)*sqrt(1-z*z);

    return vec3({x, y, z});
}

template<size_t _dim_>
inline vec<3> vec<_dim_>::reflect(const vec<3> &v, const vec<3> &n) {
    return v - 2*v.dot(n)*n;
}

template<size_t _dim_>
inline vec<3> vec<_dim_>::refract(const vec<3> &v, const vec<3> &n, DATA_TYPE etai_over_etat) {
    auto cos_theta = fmin(-v.dot(n), 1.0);
    vec3 r_out_perp = etai_over_etat * (v + cos_theta*n);
    vec3 r_out_para = -sqrt(fabs(1.0 - r_out_perp.length_squared())) * n;
    return r_out_perp + r_out_para;
}