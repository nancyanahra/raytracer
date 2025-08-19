#ifndef RTWEEKEND_HPP
#define RTWEEKEND_HPP

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <memory>

// C++ Std Usings

//using statements tell the compiler that we'll be getting shared_ptr and make_shared from the std library so we dont need to prefix these with std:: every time we reference them

using std::make_shared;
using std::shared_ptr;


// Constants

const double infinity = std::numeric_limits<double>::infinity();

const double pi = 3.1415926535897932385;

// Utility Functions

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
    
}


inline double random_double() {
    // Returns a random real in [0,1).
    return std::rand() / (RAND_MAX +1.0);
}

inline double random_double(double min, double max) {
    // returns a random real in [min, max).
    return min + (max-min)*random_double();
}

// Common Headers

#include "color.hpp"
#include "ray.hpp"
#include "vec3.hpp"
#include "interval.hpp"

#endif
    


