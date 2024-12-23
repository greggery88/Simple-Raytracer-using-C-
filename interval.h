//
// Created by Jack Williamson on 12/22/24.
//

#ifndef INTERNAL_H
#define INTERNAL_H
#include "rtpproject.h"

class interval {
  public:
    double min, max;
    interval() : min(+infinity), max(-infinity) {}; // THIS IS THE DEFUlt empty interval
    interval(double min, double max) : min(min), max(max) {}

    double size() const {
        return max - min;
    }

    bool contains(double x) const {
        return x >= min && x <= max;
    }

    bool surounds(double x) const {
        return min<x && x< max;
    }

    double clamp(double x) const {
        if (x < min) return min;
        if (x > max) return max;
        return x;
    }

    static const interval empty, universe;
};
const interval interval::empty = interval(+infinity, -infinity);
const interval interval::universe = interval(-infinity, +infinity);
#endif //INTERNAL_H
