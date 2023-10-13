#ifndef FRAME_H
#define FRAME_H

#include "size.h"
#include "point.h"

struct Frame {
    Frame() : size({0, 0}), origin({0, 0}) {};
    Frame(Point origin, Size size) : origin(origin), size(size) {};

    Point origin;
    Size size;
};

#endif
