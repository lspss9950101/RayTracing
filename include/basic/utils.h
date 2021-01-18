#pragma once

#define _DOUBLE_PRECISION_

#ifdef _DOUBLE_PRECISION_
    #define DATA_TYPE double
#else
    #define DATA_TYPE float
#endif

#include <cmath>
#include <limits>
#include <memory>
#include <random>
#include <thread>

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

namespace common {
    const double inf = std::numeric_limits<DATA_TYPE>::infinity();
    const double pi = 3.1415926535897932385;

    inline DATA_TYPE d2r(DATA_TYPE degrees) { return degrees * common::pi / 180; }
    inline DATA_TYPE random() {
        static std::uniform_real_distribution<DATA_TYPE> dis(0.0, 1.0);
        static thread_local std::mt19937 gen(std::random_device{} ());
        return dis(gen);
    }
    inline DATA_TYPE random(DATA_TYPE min, DATA_TYPE max) { return min + (max-min) * common::random(); }
    inline DATA_TYPE clamp(DATA_TYPE x, DATA_TYPE min, DATA_TYPE max) { return x > min ? x < max ? x : max : min; }
};