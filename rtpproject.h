//
// Created by Jack Williamson on 12/22/24.
//

#ifndef RTPPROJECT_H
#define RTPPROJECT_H

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <memory>
#include <string>


// C++ std usings

using std::make_shared;
using std::shared_ptr;

// Constants

const double pi = 3.14159265358979323846;
const double infinity = std::numeric_limits<double>::infinity();

//Utility Functions

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180;
}

inline double random_double() {
    return std::rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) {
    return min + (max - min) * random_double();
}

inline int random_int(int min, int max) {
    return int(random_double(min, max+1));
}

// Common Headers

#include "color.h"
#include "ray.h"
#include "vec3.h"
#include "interval.h"

#endif //RTPPROJECT_H
