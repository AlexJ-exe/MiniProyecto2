#pragma once

struct Point {
    int x;
    int y;
    
    Point(int _x, int _y);
    Point();
    
    bool operator==(const Point& other) const;
};
