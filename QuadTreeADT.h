#pragma once

#include "Node.h"

class Quad {
    Point topLeft;
    Point botRight;
    Node* n;
    Quad* topLeftTree;
    Quad* topRightTree;
    Quad* botLeftTree;
    Quad* botRightTree;

public:
    Quad();
    Quad(Point topL, Point botR);
    void insert(Node*);
    Node* search(Point);
    bool inBoundary(Point);
};