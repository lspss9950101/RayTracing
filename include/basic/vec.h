#pragma once

#include <stdlib.h>
#include <cmath>
#include <iostream>
#include <cassert>

#include <utils.h>

template<size_t _dim_>
class vec {
    static_assert(_dim_ > 0, "Dimension should be a positive integer.");

    private:
        DATA_TYPE e[_dim_];
    
    public:
        vec();
        vec(std::initializer_list<DATA_TYPE> d);

        vec<_dim_> operator-() const;
        DATA_TYPE operator[](int i) const;
        DATA_TYPE& operator[](int i);

        vec<_dim_>& operator+=(const vec<_dim_> &v);
        vec<_dim_>& operator-=(const vec<_dim_> &v);
        vec<_dim_>& operator*=(const vec<_dim_> &v);
        vec<_dim_>& operator*=(const DATA_TYPE &s);
        vec<_dim_>& operator/=(const vec<_dim_> &v);
        vec<_dim_>& operator/=(const DATA_TYPE &s);

        vec<_dim_> operator+(const vec<_dim_> &v) const;
        vec<_dim_> operator-(const vec<_dim_> &v) const;
        vec<_dim_> operator*(const vec<_dim_> &v) const;
        vec<_dim_> operator*(const DATA_TYPE &s) const;
        vec<_dim_> operator/(const vec<_dim_> &v) const;
        vec<_dim_> operator/(const DATA_TYPE &s) const;

        vec<_dim_> cross(const vec<_dim_> &v) const ;
        DATA_TYPE dot(const vec<_dim_> &v) const;

        DATA_TYPE length() const;
        DATA_TYPE length_squared() const;
        vec<_dim_> unit() const;
        bool near_zero() const;

        template<size_t _dim1_>
        friend vec<_dim1_> operator*(const DATA_TYPE &s, const vec<_dim1_> &v);
        
        template<size_t _dim1_>
        friend vec<_dim1_> cross(const vec<_dim1_> &v1, const vec<_dim1_> &v2);
        template<size_t _dim1_>
        friend DATA_TYPE dot(const vec<_dim1_> &v1, const vec<_dim1_> &v2);

        static vec<3> random();
        static vec<3> random(DATA_TYPE min, DATA_TYPE max);
        static vec<3> random_in_unit_sphere();
        static vec<3> random_on_unit_sphere();
        static vec<3> random_in_unit_disk();
        static vec<3> random_cosine_dir();
        static vec<3> random_to_sphere(DATA_TYPE radius, DATA_TYPE distance_squared);
        static vec<3> reflect(const vec<3> &v, const vec<3> &n);
        static vec<3> refract(const vec<3> &v, const vec<3> &n, DATA_TYPE etai_over_etat);
};

using vec3 = vec<3>;
using point3 = vec3;

template<size_t _dim1_>
vec<_dim1_> operator*(const DATA_TYPE &s, const vec<_dim1_> &v);

template<size_t _dim1_>
vec<_dim1_> cross(const vec<_dim1_> &v1, const vec<_dim1_> &v2);

template<size_t _dim1_>
DATA_TYPE dot(const vec<_dim1_> &v1, const vec<_dim1_> &v2);

template<size_t _dim_>
vec<_dim_> interpolate(const DATA_TYPE t, const vec<_dim_> &v1, const vec<_dim_> &v2);

template<size_t _dim_>
std::ostream& operator<<(std::ostream &os, const vec<_dim_> &v);

#include <vec.tpp>