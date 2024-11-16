#pragma once
#include <cstdint>

template <typename T>
struct Rect
{
    T left;
    T top;
    T width;
    T height;

    bool operator==(const Rect<T> &other) const
    {
        return left == other.left
            && top == other.top
            && width == other.width
            && height == other.height;
    }
};

template <typename T>
struct Point
{
    T x;
    T y;
};

using PointD = Point<double>;
using RectD = Rect<double>;
using RGBAColor = uint32_t;