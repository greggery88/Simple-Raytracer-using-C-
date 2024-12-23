//
// Created by Jack Williamson on 12/22/24.
//

#ifndef RTPPROJECT_H
#define RTPPROJECT_H

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>

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

// Common Headers

#include "color.h"
#include "ray.h"
#include "vec3.h"

#endif //RTPPROJECT_H
