#pragma once

#include "Point.h"

struct Node {
    Point pos;
    int data;
    Node(Point _pos, int _data);
    Node();
};
