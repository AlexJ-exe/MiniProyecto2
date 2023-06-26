#pragma once

#include "Node.h"
#include <list>

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
    int totalPoints();
    int totalNodes();
    void insert(Point p, int data);
    void insert(Node* node);
    void remove(Point p); // Método de eliminación
    std::list<Node*> list();
    int countRegion(Point p, int d);
    int aggregateRegion(Point p, int d);
    Node* search(Point p);
    bool inBoundary(Point p);


private:
    void countPoints(int& count);
    void countNodes(int& count);
};
