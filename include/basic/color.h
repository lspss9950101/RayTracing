#pragma once

#include <iostream>

#include <vec.h>
#include <utils.h>

using color = vec3;

void write_color(std::ostream &os, color c, int samples_per_pixel);