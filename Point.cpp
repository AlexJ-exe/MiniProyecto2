#include "Point.h"

Point::Point() : x(0), y(0) {}
Point::Point(int _x, int _y) : x(_x), y(_y) {}

bool Point::operator==(const Point& other) const {
    return x == other.x && y == other.y;
}
