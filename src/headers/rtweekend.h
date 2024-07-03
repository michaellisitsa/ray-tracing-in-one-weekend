#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <limits>
#include <memory>
#include <iostream>
#include <random>

// C++ std Usings
using std::make_shared;
using std::shared_ptr;
using std::sqrt;

// Constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility functions
inline double degrees_to_radians(double degrees)
{
    return degrees * pi / 180.0;
};

inline double random_double(double min = 0, double max = 1)
{
    static std::uniform_real_distribution<double> distribution(min, max);
    static std::mt19937 generator;
    return distribution(generator);
}

// Common Headers
#include "ray.h"
#include "vec3.h"
#include "color.h"
#include "interval.h"

#endif