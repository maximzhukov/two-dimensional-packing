#ifndef SIZE_H
#define SIZE_H

struct Size {
    Size() : width(0), height(0) {};
    Size(int width, int height) : width(width), height(height) {};

    int width;
    int height;

    friend bool operator>(const Size& lhs, const Size& rhs) {
        return lhs.width > rhs.width && lhs.height > rhs.height;
    }

    friend bool operator>(const Size& lhs, const int value) {
        return lhs.width > value && lhs.height > value;
    }

    friend bool operator>=(const Size& lhs, const int value) {
        return lhs.width >= value && lhs.height >= value;
    }
};

#endif