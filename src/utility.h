#pragma once

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <cstdlib>


// C++ Std Usings
using std::make_shared;
using std::shared_ptr;

// Constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions
inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

//returns canonical {in [0,1)} random real.
inline double random_double()
{
    return std::rand() / (RAND_MAX + 1.0);
}

//returns random real in [min, max).
inline double random_double(double min, double max)
{
    return min + random_double() * (max-min);
}

// Common Headers
#include "color.h"
#include "interval.h"
#include "ray.h"
#include "vec3.h"
