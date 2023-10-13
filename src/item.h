#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include "size.h"
#include "point.h"
#include "frame.h"

class Item {
public:
    Item() : size({0, 0}), origin({0, 0}) {}
    Item(Size size) : size(size), origin(Point()) {}

    Size size;
    Point origin;

    friend std::ostream& operator<<(std::ostream& os, const Item& item) {
        os << item.origin.x << " " 
                << item.origin.y << " " 
                << item.size.width << " " 
                << item.size.height;

        return os;
    }

    // checks that this item contains the point
    inline bool containts_point(const Point& point) const {
        if((point.x >= origin.x && point.x <= max_x()) && (point.y >= origin.y && point.y <= max_y()))
            return true;
        return false;
    }

    inline int max_x() const {
        return origin.x + size.width;
    }

    inline int max_y() const {
        return origin.y + size.height;
    }

    inline int min_x() const {
        return origin.x;
    }

    inline int min_y() const {
        return origin.y;
    }

    inline int area() const {
        return size.width * size.height;
    }
};

#endif