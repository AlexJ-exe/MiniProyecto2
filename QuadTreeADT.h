#pragma once

#include "Node.h"
#include <list>
#include <string>

class Quad {
    Point topLeft;
    Point botRight;
    Node* n;
    Quad* topLeftTree;
    Quad* topRightTree;
    Quad* botLeftTree;
    Quad* botRightTree;
    char** plane;

public:
    Quad();
    Quad(Point topL, Point botR);
    int totalPoints();
    int totalNodes();
    void insert(Point p, int data);
    void insert(Node* node);
    std::list<Node*> list();
    int countRegion(Point p, int d);
    int aggregateRegion(Point p, int d);
    Node* search(Point p);
    bool inBoundary(Point p);
    bool remove(Point p);
    std::list<Node*> searchRegion(Point p, int d);

private:
    void countPoints(int& count);
    void countNodes(int& count);
    void removeRegion(Point p, int d);
    bool inRegion(Point point, Point center, int distance);
    void aggregateDataInRegion(Point p, int d, int& sum);
    void countNodesInRegion(Point p, int d, int& count);
    bool intersectRegion(Point topLeft1, Point botRight1, Point topLeft2, Point botRight2);
    void searchNodesInRegion(Point p, int d, std::list<Node*>& nodes);
    bool removeNode(Point p, Quad& quad);
    bool inBoundary(Point p, Quad* quad);
};
